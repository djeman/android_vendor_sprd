LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_32_BIT_ONLY := true

WCND_LOCAL_CFLAGS := -DUSE_MARLIN

ifeq ($(BOARD_WLAN_DEVICE), sc2351)
WCND_LOCAL_CFLAGS :=
endif

LOCAL_CFLAGS += $(WCND_LOCAL_CFLAGS)

LOCAL_SRC_FILES:= \
	wcnd.c \
	wcnd_cmd.c \
	wcnd_worker.c \
	wcnd_sm.c \
	wcnd_download.c \
	wcnd_util.c
#	wcnd_eng_cmd_executer.c \

LOCAL_SHARED_LIBRARIES := \
	liblog \
	libcutils \
	libiwnpi \
	libnetutils
#	libengbt \
#	libengfm \


ifeq ($(BOARD_WLAN_DEVICE), bcmdhd)
LOCAL_CFLAGS += -DHAVE_SLEEPMODE_CONFIG
endif

ifeq ($(PLATFORM_VERSION),$(filter $(PLATFORM_VERSION),6.0 6.0.1))
LOCAL_CFLAGS += -DFM_ENG_DEBUG
endif

LOCAL_SRC_FILES += wcnd_eng_wifi_priv.c


LOCAL_MODULE := wcnd

LOCAL_MODULE_TAGS := optional

LOCAL_REQUIRED_MODULES := wcnd_cli

LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_EXECUTABLE)


#build wcnd_cli
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	wcnd_cli.c


LOCAL_SHARED_LIBRARIES := \
	libcutils

LOCAL_MODULE := wcnd_cli

LOCAL_MODULE_TAGS := optional

LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_EXECUTABLE)
