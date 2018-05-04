LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    libaudioril.cpp

LOCAL_SHARED_LIBRARIES :=       \
        libutils                \
        libcutils               \
	liblog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_MODULE := libaudioril
LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)

#####################################

include $(CLEAR_VARS)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_MODULE := libaudio-ril
LOCAL_SRC_FILES := libaudio-ril.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

