LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)
LOCAL_LDLIBS := -llog
LOCAL_SRC_FILES:=phasecheckserver.cpp
LOCAL_SHARED_LIBRARIES:=libutils libbinder liblog
LOCAL_MODULE_TAGS:=optional
LOCAL_MODULE:=phasecheckserver
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_EXECUTABLES)
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_EXECUTABLE)
