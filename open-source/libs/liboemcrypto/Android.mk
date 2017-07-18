LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

LOCAL_C_INCLUDES += \
		$(LOCAL_PATH)/include \
                $(TOP)/external/boringssl/src/include

LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_SRC_FILES:= \
		  src/sprdoemcrypto.c

LOCAL_MODULE := liboemcrypto
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_OWNER := sprd
LOCAL_PROPRIETARY_MODULE := true

LOCAL_SHARED_LIBRARIES := libcrypto liblog libcutils libc

include $(BUILD_SHARED_LIBRARY)
