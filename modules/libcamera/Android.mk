
LOCAL_PATH := $(call my-dir)

ISP_HW_VER := 1.0

ifeq ($(strip $(TARGET_BOARD_CAMERA_ISP_SOFTWARE_VERSION)),2)
ISP_HW_VER := 2.0
endif

ifeq ($(strip $(TARGET_BOARD_CAMERA_ISP_SOFTWARE_VERSION)),3)
ISP_HW_VER := 2.0
endif

ISP_LIB_PATH := libs/isp$(ISP_HW_VER)

TARGET_BOARD_CAMERA_READOTP_METHOD ?= 0

$(info we wanna del -DCONFIG_CAMERA_IMAGE_180 and -DCONFIG_VCM_BU64241GWZ)

######################################################
#all sprd libs
include $(LOCAL_PATH)/SprdLib.mk

#libcamcommon
include $(LOCAL_PATH)/common/Android.mk

#libcamsensor
include $(LOCAL_PATH)/sensor/Android.mk

#libcamisp1.0/libcamisp2.0
include $(LOCAL_PATH)/isp$(ISP_HW_VER)/Android.mk

#libcamoem
include $(LOCAL_PATH)/oem$(ISP_HW_VER)/Android.mk

#camera.sc8830
ifeq ($(strip $(TARGET_BOARD_CAMERA_HAL_VERSION)),1.0)
  include $(LOCAL_PATH)/hal1.0/Android.mk
else
  include $(LOCAL_PATH)/hal3/Android.mk
endif

######################################################

