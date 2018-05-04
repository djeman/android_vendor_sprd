LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	wcn_op.c wcn_tool.c

LOCAL_SHARED_LIBRARIES := \
	libcutils

LOCAL_MODULE := wcn_tool

LOCAL_MODULE_TAGS := debug

LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_EXECUTABLE)
