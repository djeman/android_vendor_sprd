
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libGLES_mali.so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_RELATIVE_PATH := egl
ifeq ($(strip $(TARGET_BUILD_VARIANT)), eng)
LOCAL_SRC_FILES := debug/libGLES_mali.so
else
LOCAL_SRC_FILES := usr/libGLES_mali.so
endif

include $(BUILD_PREBUILT)

