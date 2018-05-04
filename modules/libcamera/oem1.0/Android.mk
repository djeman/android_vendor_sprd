
ifeq ($(strip $(ISP_HW_VER)),1.0)

CUR_DIR := oem1.0

# libcamoem
include $(CLEAR_VARS)

include $(LOCAL_PATH)/SprdCtrl.mk

LOCAL_C_INCLUDES := \
	$(TOP)/vendor/sprd/modules/libcamera/common/inc \
	$(TOP)/vendor/sprd/modules/libcamera/tool/mtrace \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/arithmetic/omron/inc \
	$(TOP)/vendor/sprd/modules/libcamera/arithmetic/facebeauty/inc \
	$(TOP)/vendor/sprd/modules/libcamera/jpeg/inc \
	$(TOP)/vendor/sprd/modules/libcamera/vsp/inc \
	$(LOCAL_PATH)/$(CUR_DIR)/inc \
	$(LOCAL_PATH)/$(CUR_DIR)/isp_calibration/inc \
	$(LOCAL_PATH)/$(CUR_DIR)/inc/ydenoise_paten

LOCAL_ADDITIONAL_DEPENDENCIES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/source/include/video

LOCAL_SRC_DIR := $(LOCAL_PATH)/$(CUR_DIR)
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.c' | sed s:^$(LOCAL_PATH)/::g )

LOCAL_SRC_DIR := $(LOCAL_PATH)/jpeg
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.c' | sed s:^$(LOCAL_PATH)/::g )

LOCAL_CFLAGS += -DCHIP_ENDIAN_LITTLE -DJPEG_ENC

LOCAL_SRC_DIR := $(LOCAL_PATH)/vsp
LOCAL_SRC_FILES += $(shell find $(LOCAL_SRC_DIR) -name '*.c' | sed s:^$(LOCAL_PATH)/::g )

LOCAL_CFLAGS += -D_VSP_LINUX_ -D_VSP_

LOCAL_SHARED_LIBRARIES := libutils libcutils libcamcommon libcamsensor libcamisp$(ISP_HW_VER)

ifneq ($(strip $(TARGET_BOARD_CAMERA_FACE_BEAUTY)),false)
  LOCAL_SHARED_LIBRARIES += libts_face_beautify_hal
endif

ifeq ($(strip $(TARGET_BOARD_CAMERA_UV_DENOISE)),true)
  LOCAL_SHARED_LIBRARIES += libuvdenoise
endif

ifeq ($(strip $(TARGET_BOARD_CAMERA_Y_DENOISE)),true)
  LOCAL_SHARED_LIBRARIES += libynoise
endif

ifeq ($(strip $(TARGET_BOARD_CAMERA_SNR_UV_DENOISE)),true)
  LOCAL_SHARED_LIBRARIES += libcnr
endif

ifeq ($(strip $(TARGET_BOARD_CAMERA_HDR_CAPTURE)),true)
  #default use sprd hdr
  LOCAL_CFLAGS += -DCONFIG_SPRD_HDR_LIB

  LOCAL_SHARED_LIBRARIES += libsprd_easy_hdr
endif

ifeq ($(strip $(TARGET_BOARD_CAMERA_FACE_DETECT)),true)
  ifeq ($(strip $(TARGET_BOARD_CAMERA_FD_LIB)),omron)
    LOCAL_STATIC_LIBRARIES += libeUdnDt libeUdnCo
  else
    LOCAL_SHARED_LIBRARIES += libface_finder
  endif
endif

LOCAL_MODULE := libcamoem
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)

endif
