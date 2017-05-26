/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2014 The CyanogenMod Project
 * Copyright (C) 2014-2015 Andreas Schneider <asn@cryptomilk.org>
 * Copyright (C) 2014-2015 Christopher N. Hesse <raymanfx@gmail.com>
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

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#define LOG_TAG "SEC PowerHAL"
/* #define LOG_NDEBUG 0 */
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

#define BOOSTPULSE_PATH "/sys/devices/system/cpu/cpufreq/interactive/boostpulse"

struct sec_power_module {
    struct power_module base;
    pthread_mutex_t lock;
    int boostpulse_fd;
    int boostpulse_warned;
};

/**********************************************************
 *** HELPER FUNCTIONS
 **********************************************************/

static int sysfs_read(char *path, char *s, int num_bytes)
{
    char errno_str[64];
    int len;
    int ret = 0;
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        strerror_r(errno, errno_str, sizeof(errno_str));
        ALOGE("Error opening %s: %s\n", path, errno_str);

        return -1;
    }

    len = read(fd, s, num_bytes - 1);
    if (len < 0) {
        strerror_r(errno, errno_str, sizeof(errno_str));
        ALOGE("Error reading from %s: %s\n", path, errno_str);

        ret = -1;
    } else {
        s[len] = '\0';
    }

    close(fd);

    return ret;
}

static void sysfs_write(const char *path, char *s)
{
    char errno_str[64];
    int len;
    int fd;

    fd = open(path, O_WRONLY);
    if (fd < 0) {
        strerror_r(errno, errno_str, sizeof(errno_str));
        ALOGE("Error opening %s: %s\n", path, errno_str);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, errno_str, sizeof(errno_str));
        ALOGE("Error writing to %s: %s\n", path, errno_str);
    }

    close(fd);
}

/**********************************************************
 *** POWER FUNCTIONS
 **********************************************************/

/* You need to request the powerhal lock before calling this function */
static int boostpulse_open(struct sec_power_module *sec_pwr)
{
    char errno_str[64];

    if (sec_pwr->boostpulse_fd < 0) {
        sec_pwr->boostpulse_fd = open(BOOSTPULSE_PATH, O_WRONLY);
        if (sec_pwr->boostpulse_fd < 0) {
            if (!sec_pwr->boostpulse_warned) {
                strerror_r(errno, errno_str, sizeof(errno_str));
                ALOGE("Error opening %s: %s\n", BOOSTPULSE_PATH, errno_str);
                sec_pwr->boostpulse_warned = 1;
            }
        }
    }

    return sec_pwr->boostpulse_fd;
}

/**********************************************************
 *** INIT FUNCTIONS
 **********************************************************/

/*
 * The init function performs power management setup actions at runtime
 * startup, such as to set default cpufreq parameters.  This is called only by
 * the Power HAL instance loaded by PowerManagerService.
 */
static void sec_power_init(struct power_module *module)
{
    (void) module; /* unused */
}

/*
 * The setInteractive function performs power management actions upon the
 * system entering interactive state (that is, the system is awake and ready
 * for interaction, often with UI devices such as display and touchscreen
 * enabled) or non-interactive state (the system appears asleep, display
 * usually turned off).  The non-interactive state is usually entered after a
 * period of inactivity, in order to conserve battery power during such
 * inactive periods.
 *
 * Typical actions are to turn on or off devices and adjust cpufreq parameters.
 * This function may also call the appropriate interfaces to allow the kernel
 * to suspend the system to low-power sleep state when entering non-interactive
 * state, and to disallow low-power suspend when the system is in interactive
 * state.  When low-power suspend state is allowed, the kernel may suspend the
 * system whenever no wakelocks are held.
 *
 * on is non-zero when the system is transitioning to an interactive / awake
 * state, and zero when transitioning to a non-interactive / asleep state.
 *
 * This function is called to enter non-interactive state after turning off the
 * screen (if present), and called to enter interactive state prior to turning
 * on the screen.
 */
static void sec_power_set_interactive(struct power_module *module, int on)
{
    (void) module; /* unused */
    (void) on; /* unused */
}

/*
 * The powerHint function is called to pass hints on power requirements, which
 * may result in adjustment of power/performance parameters of the cpufreq
 * governor and other controls.
 *
 * The possible hints are:
 *
 * POWER_HINT_VSYNC
 *
 *     Foreground app has started or stopped requesting a VSYNC pulse
 *     from SurfaceFlinger.  If the app has started requesting VSYNC
 *     then CPU and GPU load is expected soon, and it may be appropriate
 *     to raise speeds of CPU, memory bus, etc.  The data parameter is
 *     non-zero to indicate VSYNC pulse is now requested, or zero for
 *     VSYNC pulse no longer requested.
 *
 * POWER_HINT_INTERACTION
 *
 *     User is interacting with the device, for example, touchscreen
 *     events are incoming.  CPU and GPU load may be expected soon,
 *     and it may be appropriate to raise speeds of CPU, memory bus,
 *     etc.  The data parameter is unused.
 *
 * POWER_HINT_LOW_POWER
 *
 *     Low power mode is activated or deactivated. Low power mode
 *     is intended to save battery at the cost of performance. The data
 *     parameter is non-zero when low power mode is activated, and zero
 *     when deactivated.
 *
 * POWER_HINT_CPU_BOOST
 *
 *     An operation is happening where it would be ideal for the CPU to
 *     be boosted for a specific duration. The data parameter is an
 *     integer value of the boost duration in microseconds.
 */
static void sec_power_hint(struct power_module *module,
                                  power_hint_t hint,
                                  void *data)
{
    struct sec_power_module *sec_pwr = (struct sec_power_module *) module;

    switch (hint) {
        case POWER_HINT_INTERACTION: {
            char errno_str[64];
            ssize_t len;
            int fd;

            pthread_mutex_lock(&sec_pwr->lock);
            fd = boostpulse_open(sec_pwr);
            pthread_mutex_unlock(&sec_pwr->lock);

            if (fd >= 0) {
                len = write(sec_pwr->boostpulse_fd, "1", 1);

                if (len < 0) {
                    strerror_r(errno, errno_str, sizeof(errno_str));
                    ALOGE("Error writing to %s: %s\n", BOOSTPULSE_PATH, errno_str);
                }
            }

            break;
        }
        default:
            break;
    }

    (void) data; /* unused */
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct sec_power_module HAL_MODULE_INFO_SYM = {
    .base = {
        .common = {
            .tag = HARDWARE_MODULE_TAG,
            .module_api_version = POWER_MODULE_API_VERSION_0_2,
            .hal_api_version = HARDWARE_HAL_API_VERSION,
            .id = POWER_HARDWARE_MODULE_ID,
            .name = "SEC Power HAL",
            .author = "The Android Open Source Project",
            .methods = &power_module_methods,
        },

        .init = sec_power_init,
        .setInteractive = sec_power_set_interactive,
        .powerHint = sec_power_hint
    },

    .lock = PTHREAD_MUTEX_INITIALIZER,
    .boostpulse_fd = -1,
    .boostpulse_warned = 0,
};
