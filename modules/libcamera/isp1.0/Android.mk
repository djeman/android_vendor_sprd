
ifeq ($(strip $(ISP_HW_VER)),1.0)

CUR_DIR := isp1.0

# libcamisp1.0
include $(CLEAR_VARS)

include $(LOCAL_PATH)/SprdCtrl.mk

LOCAL_C_INCLUDES := \
	$(TOP)/system/media/camera/include \
	$(TOP)/vendor/sprd/modules/libcamera/common/inc \
	$(TOP)/vendor/sprd/modules/libcamera/tool/mtrace \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/isp_calibration/inc \
	$(TOP)/vendor/sprd/modules/libcamera/$(CUR_DIR)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/$(CUR_DIR)/uv_denoise/inc

LOCAL_ADDITIONAL_DEPENDENCIES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/source/include/video

LOCAL_SRC_DIR := $(LOCAL_PATH)/$(CUR_DIR)

LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.c' | sed s:^$(LOCAL_PATH)/::g )

LOCAL_SHARED_LIBRARIES := libutils libcutils libcamcommon libcamsensor
LOCAL_SHARED_LIBRARIES += libae libawb libaf liblsc libev

LOCAL_MODULE := libcamisp1.0
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)

endif
