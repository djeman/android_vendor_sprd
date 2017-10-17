
CUR_DIR := hal1.0

ifeq ($(strip $(TARGET_BOARD_CAMERA_HAL_VERSION)),1.0)

include $(CLEAR_VARS)

include $(LOCAL_PATH)/SprdCtrl.mk

LOCAL_C_INCLUDES := \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/isp_tune \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/isp_app \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/calibration/inc \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/isp_calibration/inc \
	$(TOP)/vendor/sprd/modules/libcamera/arithmetic/inc \
	$(TOP)/vendor/sprd/modules/libcamera/arithmetic/omron/inc \
	$(TOP)/vendor/sprd/modules/libcamera/arithmetic/facebeauty/inc \
	$(TOP)/vendor/sprd/modules/libcamera/common/inc \
	$(TOP)/vendor/sprd/modules/libcamera/tool/mtrace \
	$(TOP)/vendor/sprd/modules/libcamera/tool/auto_test/inc \
	$(TOP)/external/skia/include/images \
	$(TOP)/external/skia/include/core\
	$(TOP)/external/jhead \
	$(TOP)/external/sqlite/dist \
	$(TOP)/system/media/camera/include \
	$(TOP)/frameworks/native/include/media/openmax \
	$(TOP)/vendor/sprd/open-source/libs/libmemoryheapion

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/$(CUR_DIR)/inc \
	$(LOCAL_PATH)/$(CUR_DIR)

LOCAL_ADDITIONAL_DEPENDENCIES := \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/source/include/video

ifeq ($(strip $(TARGET_GPU_PLATFORM)),midgard)
  LOCAL_C_INCLUDES += $(TOP)/vendor/sprd/modules/libgpu/gralloc/midgard
else
  LOCAL_C_INCLUDES += $(TOP)/vendor/sprd/modules/libgpu/gralloc/utgard
endif

LOCAL_SRC_DIR := $(LOCAL_PATH)/$(CUR_DIR)
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.c' | sed s:^$(LOCAL_PATH)/::g )
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.cpp' | sed s:^$(LOCAL_PATH)/::g )

LOCAL_SRC_DIR := $(LOCAL_PATH)/tool
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.c' | sed s:^$(LOCAL_PATH)/::g )
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.cpp' | sed s:^$(LOCAL_PATH)/::g )

LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE := camera.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libutils libmemoryheapion libcamera_client libcutils libhardware libcamera_metadata libdl
LOCAL_SHARED_LIBRARIES += libui libbinder libcamcommon libcamsensor libcamisp$(ISP_HW_VER)

ifneq ($(strip $(TARGET_BOARD_CAMERA_FACE_BEAUTY)),false)
  LOCAL_SHARED_LIBRARIES += libts_face_beautify_hal
endif

#use media extension
ifeq ($(TARGET_USES_MEDIA_EXTENSIONS), true)
  LOCAL_CFLAGS += -DUSE_MEDIA_EXTENSIONS
endif

include $(BUILD_SHARED_LIBRARY)

endif
