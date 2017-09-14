/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2014 The CyanogenMod Project
 * Copyright (C) 2014-2015 Andreas Schneider <asn@cryptomilk.org>
 * Copyright (C) 2014-2017 Christopher N. Hesse <raymanfx@gmail.com>
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>

#define LOG_TAG "SamsungPowerHAL"
/* #define LOG_NDEBUG 0 */
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

#define CPU_SYSFS_PATH "/sys/devices/system/cpu/cpu0"
#define CPU_INTERACTIVE_PATH "/sys/devices/system/cpu/cpufreq/interactive"

#define BOOST_PATH        "/boost"
#define BOOSTPULSE_PATH   "/boostpulse"

#define IO_IS_BUSY_PATH   "/io_is_busy"
#define HISPEED_FREQ_PATH "/hispeed_freq"

#define MAX_FREQ_PATH     "/cpufreq/scaling_max_freq"

#define PARAM_MAXLEN      10

#define ARRAY_SIZE(a)     sizeof(a) / sizeof(a[0])

struct samsung_power_module {
    struct power_module base;
    pthread_mutex_t lock;
    int boost_fd;
    int boostpulse_fd;
    char hispeed_freq[PARAM_MAXLEN];
    char max_freq[PARAM_MAXLEN];
};

enum power_profile_e {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_MAX
};

static enum power_profile_e current_power_profile = PROFILE_BALANCED;

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
        ALOGE("Error opening %s: %s", path, errno_str);

        return -1;
    }

    len = read(fd, s, num_bytes - 1);
    if (len < 0) {
        strerror_r(errno, errno_str, sizeof(errno_str));
        ALOGE("Error reading from %s: %s", path, errno_str);

        ret = -1;
    } else {
        // do not store newlines, but terminate the string instead
        if (s[len-1] == '\n') {
            s[len-1] = '\0';
        } else {
            s[len] = '\0';
        }
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
        ALOGE("Error opening %s: %s", path, errno_str);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, errno_str, sizeof(errno_str));
        ALOGE("Error writing to %s: %s", path, errno_str);
    }

    close(fd);
}

static void cpu_sysfs_read(const char *param, char s[PARAM_MAXLEN])
{
    char path[PATH_MAX];

    sprintf(path, "%s%s", CPU_SYSFS_PATH, param);
    sysfs_read(path, s, PARAM_MAXLEN);
}

static void cpu_sysfs_write(const char *param, char s[PARAM_MAXLEN])
{
    char path[PATH_MAX];

    sprintf(path, "%s%s", CPU_SYSFS_PATH, param);
    sysfs_write(path, s);
}

static void cpu_interactive_read(const char *param, char s[PARAM_MAXLEN])
{
    char path[PATH_MAX];

    sprintf(path, "%s%s", CPU_INTERACTIVE_PATH, param);
    sysfs_read(path, s, PARAM_MAXLEN);
}

static void cpu_interactive_write(const char *param, char s[PARAM_MAXLEN])
{
    char path[PATH_MAX];

    sprintf(path, "%s%s", CPU_INTERACTIVE_PATH, param);
    sysfs_write(path, s);
}

static void send_boost(int boost_fd, int32_t duration_us)
{
    int len;

    if (boost_fd < 0) {
        return;
    }

    len = write(boost_fd, "1", 1);
    if (len < 0) {
        ALOGE("Error writing to %s%s: %s", CPU_INTERACTIVE_PATH, BOOST_PATH, strerror(errno));
        return;
    }

    usleep(duration_us);
    len = write(boost_fd, "0", 1);
}

static void send_boostpulse(int boostpulse_fd)
{
    int len;

    if (boostpulse_fd < 0) {
        return;
    }

    len = write(boostpulse_fd, "1", 1);
    if (len < 0) {
        ALOGE("Error writing to %s%s: %s", CPU_INTERACTIVE_PATH, BOOSTPULSE_PATH,
                strerror(errno));
    }
}

/**********************************************************
 *** POWER FUNCTIONS
 **********************************************************/

static void set_power_profile(struct samsung_power_module *samsung_pwr,
                              int profile)
{
    int rc;

    if (profile < 0 || profile >= PROFILE_MAX) {
        return;
    }

    if (current_power_profile == profile) {
        return;
    }

    ALOGV("%s: profile=%d", __func__, profile);

    switch (profile) {
        case PROFILE_POWER_SAVE:
            // Grab value set by init.*.rc
            cpu_interactive_read(HISPEED_FREQ_PATH, samsung_pwr->hispeed_freq);
            // Limit to hispeed freq
            cpu_sysfs_write(MAX_FREQ_PATH, samsung_pwr->hispeed_freq);
            ALOGV("%s: set powersave mode", __func__);
            break;
        case PROFILE_BALANCED:
            // Restore normal max freq
            cpu_sysfs_write(MAX_FREQ_PATH, samsung_pwr->max_freq);
            ALOGV("%s: set balanced mode", __func__);
            break;
        case PROFILE_HIGH_PERFORMANCE:
            // Restore normal max freq
            cpu_sysfs_write(MAX_FREQ_PATH, samsung_pwr->max_freq);
            ALOGV("%s: set performance mode", __func__);
            break;
        default:
            ALOGW("%s: Unknown power profile: %d", __func__, profile);
            return;
    }

    current_power_profile = profile;
}

/**********************************************************
 *** INIT FUNCTIONS
 **********************************************************/

static void init_cpufreqs(struct samsung_power_module *samsung_pwr)
{
    cpu_interactive_read(HISPEED_FREQ_PATH, samsung_pwr->hispeed_freq);
    cpu_sysfs_read(MAX_FREQ_PATH, samsung_pwr->max_freq);
}

static void boost_open(struct samsung_power_module *samsung_pwr)
{
    char path[PATH_MAX];

    // the boost node is only valid for the LITTLE cluster
    sprintf(path, "%s%s", CPU_INTERACTIVE_PATH, BOOST_PATH);

    samsung_pwr->boost_fd = open(path, O_WRONLY);
    if (samsung_pwr->boost_fd < 0) {
        ALOGE("Error opening %s: %s\n", path, strerror(errno));
    }
}

static void boostpulse_open(struct samsung_power_module *samsung_pwr)
{
    char path[PATH_MAX];

    // the boostpulse node is only valid for the LITTLE cluster
    sprintf(path, "%s%s", CPU_INTERACTIVE_PATH, BOOSTPULSE_PATH);

    samsung_pwr->boostpulse_fd = open(path, O_WRONLY);
    if (samsung_pwr->boostpulse_fd < 0) {
        ALOGE("Error opening %s: %s\n", path, strerror(errno));
    }
}

static void samsung_power_init(struct power_module *module)
{
    struct samsung_power_module *samsung_pwr = (struct samsung_power_module *) module;

    init_cpufreqs(samsung_pwr);

    // keep interactive boost fds opened
    boost_open(samsung_pwr);
    boostpulse_open(samsung_pwr);

    ALOGI("Initialized settings:");
    ALOGI("max_freq: %s", samsung_pwr->max_freq);
    ALOGI("hispeed_freq: %s", samsung_pwr->hispeed_freq);
    ALOGI("boostpulse_fd: %d", samsung_pwr->boostpulse_fd);
}

/**********************************************************
 *** API FUNCTIONS
 ***
 *** Refer to power.h for documentation.
 **********************************************************/

static void samsung_power_set_interactive(struct power_module *module, int on)
{
    char ON[PARAM_MAXLEN]  = {"1"};
    char OFF[PARAM_MAXLEN] = {"0"};

    cpu_interactive_write(IO_IS_BUSY_PATH, on ? ON : OFF);

    ALOGV("power_set_interactive: %d done", on);
}

static void samsung_power_hint(struct power_module *module,
                                  power_hint_t hint,
                                  void *data)
{
    struct samsung_power_module *samsung_pwr = (struct samsung_power_module *) module;
    int len;

    /* Bail out if low-power mode is active */
    if (current_power_profile == PROFILE_POWER_SAVE && hint != POWER_HINT_LOW_POWER
            && hint != POWER_HINT_SET_PROFILE) {
        return;
    }

    switch (hint) {
        case POWER_HINT_VSYNC:
            ALOGV("%s: POWER_HINT_VSYNC", __func__);
            break;
        case POWER_HINT_INTERACTION:
            ALOGV("%s: POWER_HINT_INTERACTION", __func__);
            send_boostpulse(samsung_pwr->boostpulse_fd);
            break;
        case POWER_HINT_LOW_POWER:
            ALOGV("%s: POWER_HINT_LOW_POWER", __func__);
            set_power_profile(samsung_pwr, data ? PROFILE_POWER_SAVE : PROFILE_BALANCED);
            break;
        case POWER_HINT_LAUNCH:
            ALOGV("%s: POWER_HINT_LAUNCH", __func__);
            send_boostpulse(samsung_pwr->boostpulse_fd);
            break;
        case POWER_HINT_CPU_BOOST:
            ALOGV("%s: POWER_HINT_CPU_BOOST", __func__);
            int32_t duration_us = *((int32_t *)data);
            send_boost(samsung_pwr->boost_fd, duration_us);
            break;
        case POWER_HINT_SET_PROFILE:
            ALOGV("%s: POWER_HINT_SET_PROFILE", __func__);
            int profile = *((intptr_t *)data);
            set_power_profile(samsung_pwr, profile);
            break;
        default:
            ALOGW("%s: Unknown power hint: %d", __func__, hint);
            break;
    }
}

static int samsung_get_feature(struct power_module *module __unused,
                               feature_t feature)
{
    if (feature == POWER_FEATURE_SUPPORTED_PROFILES) {
        return PROFILE_MAX;
    }

    return -1;
}

static void samsung_set_feature(struct power_module *module, feature_t feature, int state __unused)
{
    struct samsung_power_module *samsung_pwr = (struct samsung_power_module *) module;

    switch (feature) {
#ifdef TARGET_TAP_TO_WAKE_NODE
        case POWER_FEATURE_DOUBLE_TAP_TO_WAKE:
            ALOGV("%s: %s double tap to wake", __func__, state ? "enabling" : "disabling");
            sysfs_write(TARGET_TAP_TO_WAKE_NODE, state > 0 ? "1" : "0");
            break;
#endif
        default:
            break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct samsung_power_module HAL_MODULE_INFO_SYM = {
    .base = {
        .common = {
            .tag = HARDWARE_MODULE_TAG,
            .module_api_version = POWER_MODULE_API_VERSION_0_2,
            .hal_api_version = HARDWARE_HAL_API_VERSION,
            .id = POWER_HARDWARE_MODULE_ID,
            .name = "Samsung Power HAL",
            .author = "The LineageOS Project",
            .methods = &power_module_methods,
        },

        .init = samsung_power_init,
        .setInteractive = samsung_power_set_interactive,
        .powerHint = samsung_power_hint,
        .getFeature = samsung_get_feature,
        .setFeature = samsung_set_feature
    },

    .lock = PTHREAD_MUTEX_INITIALIZER,
    .boostpulse_fd = -1,
};
