
CUR_DIR := common

include $(CLEAR_VARS)

include $(LOCAL_PATH)/SprdCtrl.mk

LOCAL_C_INCLUDES := \
	$(TOP)/vendor/sprd/modules/libcamera/common/inc \
	$(TOP)/vendor/sprd/modules/libcamera/tool/mtrace \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/isp_calibration/inc \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/isp_app \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/inc

LOCAL_ADDITIONAL_DEPENDENCIES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/source/include/video

LOCAL_SRC_FILES := \
	$(CUR_DIR)/src/cmr_msg.c

LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_MODULE := libcamcommon
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)

