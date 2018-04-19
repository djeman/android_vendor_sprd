/*
 * Copyright (C) 2015 The CyanogenMod Project
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/sensors.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <utils/Log.h>

/* Local includes */
#include "sensors.h"
#include "AccelerometerSensor.h"
#include "ProximitySensor.h"
#include "MetaEvent.h"

/*****************************************************************************/

#define SENSORS_ACCELERATION_HANDLE       (ID_A)
#define SENSORS_MAGNETIC_FIELD_HANDLE     (ID_M)
#define SENSORS_ORIENTATION_HANDLE        (ID_O)
#define SENSORS_LIGHT_HANDLE              (ID_L)
#define SENSORS_PROXIMITY_HANDLE          (ID_P)
#define SENSORS_SCREEN_ORIENTATION_HANDLE (ID_SO)
#define SENSORS_SIGNIFICANT_MOTION_HANDLE (ID_SM)
#define SENSORS_GYROSCOPE_HANDLE          (ID_GY)

#define	SENSORS_HRM_HANDLE				  (ID_HRM)
#define SENSORS_GESTURE_HANDLE			  (ID_GES)
#define SENSORS_STEP_DETECT_HANDLE		  (ID_STD)
#define SENSORS_STEP_COUNT_HANDLE		  (ID_STC)
#define SENSORS_ROTATION_VECTOR_HANDLE	  (ID_ROT)
#define SENSORS_PRESSURE_HANDLE			  (ID_PRS)
#define SENSORS_TEMPERATURE_HANDLE		  (ID_PRS)

/*****************************************************************************/

static struct sensor_t sSensorList[] = {
    {
        .name = "BMA254 Acceleration Sensor",
        .vendor = "Bosch Sensortec",
        .version = 1,
        .handle = SENSORS_ACCELERATION_HANDLE,
        .type = SENSOR_TYPE_ACCELEROMETER,
        .maxRange = RANGE_A, // 39,2266
        .resolution = CONVERT_A, // 0,0196133
        .power = 0.13,
        .minDelay = 10000,
        .fifoReservedEventCount = 0,
        .fifoMaxEventCount = 0,
        .stringType = SENSOR_STRING_TYPE_ACCELEROMETER,
        .requiredPermission = 0,
        .maxDelay = ACC_MAX_DELAY_NS,
        .flags = SENSOR_FLAG_CONTINUOUS_MODE,
        .reserved = {}
    },
    {
        .name = "CM36672P Proximity Sensor",
        .vendor = "Capella Microsystems, Inc.",
        .version = 1,
        .handle = SENSORS_PROXIMITY_HANDLE,
        .type = SENSOR_TYPE_PROXIMITY,
        .maxRange = 8.0,
        .resolution = 8.0,
        .power = 0.75,
        .minDelay = 0,
        .fifoReservedEventCount = 0,
        .fifoMaxEventCount = 0,
        .stringType = SENSOR_STRING_TYPE_PROXIMITY,
        .requiredPermission = 0,
        .maxDelay = 0,
        .flags = SENSOR_FLAG_WAKE_UP | SENSOR_FLAG_ON_CHANGE_MODE,
        .reserved = {}
    }
};

static int open_sensors(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device);

static int sensors__get_sensors_list(struct sensors_module_t*,
                                     struct sensor_t const** list)
{
        *list = sSensorList;
        return ARRAY_SIZE(sSensorList);
}

static struct hw_module_methods_t sensors_module_methods = {
        .open = open_sensors,
};

struct sensors_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 3,
        .id = SENSORS_HARDWARE_MODULE_ID,
        .name = "Samsung Sensor module",
        .author = "Samsung Electronic Company",
        .methods = &sensors_module_methods,
        .dso = NULL,
        .reserved = {0}
    },
    .get_sensors_list = sensors__get_sensors_list,
    //.set_operation_mode = NULL,
};

struct sensors_poll_context_t {
    sensors_poll_device_1_t device; // must be first

    sensors_poll_context_t();
    ~sensors_poll_context_t();
    int activate(int handle, int enabled);
    int setDelay(int handle, int64_t ns);
    int pollEvents(sensors_event_t* data, int count);
    int batch(int handle, int flags, int64_t period_ns, int64_t timeout);
    int flush(int handle);

private:
    enum {
        accel = 0,
        prox,
        meta,
        numSensorDrivers,

        numFds,
    };

    static const size_t wake = numFds - 1;
    static const char WAKE_MESSAGE = 'W';
    struct pollfd mPollFds[numFds];
    int mWritePipeFd;
    SensorBase* mSensors[numSensorDrivers];

    int handleToDriver(int handle) const {
        switch (handle) {
        case ID_P:
            return prox;
        default:
            return -EINVAL;
        }
    }
};

/*****************************************************************************/

sensors_poll_context_t::sensors_poll_context_t()
{
    mSensors[accel] = new AccelerometerSensor();
    mPollFds[accel].fd = mSensors[accel]->getFd();
    mPollFds[accel].events = POLLIN;
    mPollFds[accel].revents = 0;
	
    mSensors[prox] = new ProximitySensor();
    mPollFds[prox].fd = mSensors[prox]->getFd();
    mPollFds[prox].events = POLLIN;
    mPollFds[prox].revents = 0;

    mSensors[meta] = new MetaEvent();
    mPollFds[meta].fd = mSensors[meta]->getFd();
    mPollFds[meta].events = POLLIN;
    mPollFds[meta].revents = 0;
	
    int wakeFds[2];
    int result = pipe(wakeFds);
    ALOGE_IF(result < 0, "error creating wake pipe (%s)", strerror(errno));
    fcntl(wakeFds[0], F_SETFL, O_NONBLOCK);
    fcntl(wakeFds[1], F_SETFL, O_NONBLOCK);
    mWritePipeFd = wakeFds[1];

    mPollFds[wake].fd = wakeFds[0];
    mPollFds[wake].events = POLLIN;
    mPollFds[wake].revents = 0;
}

sensors_poll_context_t::~sensors_poll_context_t()
{
    for (int i = 0 ; i < numSensorDrivers ; i++) {
        delete mSensors[i];
    }
    close(mPollFds[wake].fd);
    close(mWritePipeFd);
}

int sensors_poll_context_t::activate(int handle, int enabled)
{
    int index = handleToDriver(handle);

    if (index < 0)
        return index;

    int err = mSensors[index]->enable(handle, enabled);
    if (enabled && !err) {
        const char wakeMessage(WAKE_MESSAGE);
        int result = write(mWritePipeFd, &wakeMessage, 1);
        ALOGE_IF(result < 0, "error sending wake message (%s)", strerror(errno));
    }

    return err;
}

int sensors_poll_context_t::setDelay(int handle, int64_t ns)
{
    int index = handleToDriver(handle);
    int ret = 0;

    if (index < 0)
        return index;

    ret = mSensors[index]->setDelay(handle, ns);

    return ret;
}

int sensors_poll_context_t::pollEvents(sensors_event_t* data, int count)
{
    int nbEvents = 0;
    int n = 0;

    do {
        // see if we have some leftover from the last poll()
        for (int i = 0; count && i < numSensorDrivers; i++) {
            SensorBase* const sensor(mSensors[i]);
            if ((mPollFds[i].revents & POLLIN) || (sensor->hasPendingEvents())) {
                int nb = sensor->readEvents(data, count);
                if (nb < count) {
                    // no more data for this sensor
                    mPollFds[i].revents = 0;
                }
                count -= nb;
                nbEvents += nb;
                data += nb;
            }
        }

        if (count) {
            // we still have some room, so try to see if we can get
            // some events immediately or just wait if we don't have
            // anything to return
            do {
                n = poll(mPollFds, numFds, nbEvents ? 0 : -1);
            } while (n < 0 && errno == EINTR);
            if (n < 0) {
                ALOGE("poll() failed (%s)", strerror(errno));
                return -errno;
            }
            if (mPollFds[wake].revents & POLLIN) {
                char msg;
                int result = read(mPollFds[wake].fd, &msg, 1);
                ALOGE_IF(result < 0, "error reading from wake pipe (%s)", strerror(errno));
                ALOGE_IF(msg != WAKE_MESSAGE, "unknown message on wake queue (0x%02x)", int(msg));

                mPollFds[wake].revents = 0;
            }
        }
        // if we have events and space, go read them
    } while (n && count);

    return nbEvents;
}

int sensors_poll_context_t::batch(int handle, int flags, int64_t period_ns,
                                  int64_t timeout)
{
    int index = handleToDriver(handle);

    if (index < 0)
        return index;

    return mSensors[index]->batch(handle, flags, period_ns, timeout);
}

int sensors_poll_context_t::flush(int handle)
{
    int index = handleToDriver(handle);

    if (index < 0)
        return index;

    return mSensors[index]->flush(handle);
}

/*****************************************************************************/

static int poll__close(struct hw_device_t *dev)
{
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    if (ctx) {
        delete ctx;
    }
    return 0;
}

static int poll__activate(struct sensors_poll_device_t *dev,
        int handle, int enabled)
{
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->activate(handle, enabled);
}

static int poll__setDelay(struct sensors_poll_device_t *dev,
        int handle, int64_t ns)
{
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->setDelay(handle, ns);
}

static int poll__poll(struct sensors_poll_device_t *dev,
        sensors_event_t* data, int count)
{
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->pollEvents(data, count);
}

static int poll__batch(struct sensors_poll_device_1 *dev,
                      int handle, int flags, int64_t period_ns, int64_t timeout)
{
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev; 
    return ctx->batch(handle, flags, period_ns, timeout);
}

static int poll__flush(struct sensors_poll_device_1 *dev,
                      int handle)
{
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->flush(handle);
}

/*****************************************************************************/

/** Open a new instance of a sensor device using name */
static int open_sensors(const struct hw_module_t* module, const char*,
                        struct hw_device_t** device)
{
    int status = -EINVAL;
    sensors_poll_context_t *dev = new sensors_poll_context_t();

    memset(&dev->device, 0, sizeof(sensors_poll_device_1));

    dev->device.common.tag = HARDWARE_DEVICE_TAG;
    dev->device.common.version  = SENSORS_DEVICE_API_VERSION_1_3;
    dev->device.common.module   = const_cast<hw_module_t*>(module);
    dev->device.common.close    = poll__close;
    dev->device.activate        = poll__activate;
    dev->device.setDelay        = poll__setDelay;
    dev->device.poll            = poll__poll;
    dev->device.batch           = poll__batch;
    dev->device.flush           = poll__flush;

    *device = &dev->device.common;
    status = 0;

    return status;
}

