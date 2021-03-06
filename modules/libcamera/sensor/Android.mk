
CUR_DIR := sensor

include $(CLEAR_VARS)

include $(LOCAL_PATH)/SprdCtrl.mk

LOCAL_C_INCLUDES := \
	$(TOP)/vendor/sprd/modules/libcamera/common/inc \
	$(TOP)/vendor/sprd/modules/libcamera/tool/mtrace \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/oem$(ISP_HW_VER)/isp_calibration/inc \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/isp_app \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/ae/inc \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/awb/inc \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/inc \
	$(TOP)/vendor/sprd/modules/libcamera/isp$(ISP_HW_VER)/utility

LOCAL_ADDITIONAL_DEPENDENCIES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/source/include/video

ifeq ($(strip $(ISP_HW_VER)),2.0)
LOCAL_SRC_FILES := \
                $(CUR_DIR)/vcm_dw9714a.c \
                $(CUR_DIR)/ov5640/sensor_ov5640_mipi.c \
                $(CUR_DIR)/ov5640/sensor_ov5640_mipi_raw.c \
                $(CUR_DIR)/ov5670/sensor_ov5670_mipi_raw.c \
                $(CUR_DIR)/c2590/sensor_c2590_mipi_raw.c \
                $(CUR_DIR)/gc2155/sensor_gc2155_mipi.c \
                $(CUR_DIR)/ov8825/sensor_ov8825_mipi_raw.c \
                $(CUR_DIR)/hi544/sensor_hi544_mipi_raw.c \
                $(CUR_DIR)/hi255/sensor_hi255.c \
                $(CUR_DIR)/sensor_gc0310_mipi.c \
                $(CUR_DIR)/ov5648/sensor_ov5648_mipi_raw.c \
                $(CUR_DIR)/ov5648_darling/sensor_ov5648_darling_mipi_raw.c \
                $(CUR_DIR)/ov13850/sensor_ov13850_mipi_raw.c \
                $(CUR_DIR)/ov13850r2a/sensor_ov13850r2a_mipi_raw.c \
                $(CUR_DIR)/ov8858/sensor_ov8858_mipi_raw.c \
                $(CUR_DIR)/ov2680/sensor_ov2680_mipi_raw.c \
                $(CUR_DIR)/s5k4h5yc/sensor_s5k4h5yc_mipi_raw.c \
                $(CUR_DIR)/s5k5e3yx/sensor_s5k5e3yx_mipi_raw.c \
                $(CUR_DIR)/s5k4h5yc/sensor_s5k4h5yc_mipi_raw_jsl.c \
                $(CUR_DIR)/s5k3l2xx/sensor_s5k3l2xx_mipi_raw.c \
                $(CUR_DIR)/imx132/sensor_imx132_mipi_raw.c \
                $(CUR_DIR)/s5k3m2xxm3/sensor_s5k3m2xxm3_mipi_raw.c \
                $(CUR_DIR)/imx214/sensor_imx214_mipi_raw.c \
                $(CUR_DIR)/s5k4h5yc/packet_convert.c \
                $(CUR_DIR)/sensor_autotest_ov5648_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_ov5670_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_ov13850_mipi_raw.c

LOCAL_SRC_FILES += \
                $(CUR_DIR)/oem/sensor_v2_cfg.c \
                $(CUR_DIR)/oem/sensor_v2_drv_u.c \
                $(CUR_DIR)/oem/sensor_v2_isp_param_merge.c \
                $(CUR_DIR)/oem/sensor_v2_isp_param_awb_pac.c \
                $(CUR_DIR)/isp/isp_v2_param_file_update.c
else
LOCAL_SRC_FILES := \
                $(CUR_DIR)/sensor_ov8825_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_ov8825_mipi_raw.c\
                $(CUR_DIR)/sensor_ov13850_mipi_raw.c \
                $(CUR_DIR)/sensor_ov5648_mipi_raw.c \
                $(CUR_DIR)/sensor_ov5670_mipi_raw.c \
                $(CUR_DIR)/sensor_ov2680_mipi_raw.c \
                $(CUR_DIR)/sensor_ov8858_mipi_raw.c \
                $(CUR_DIR)/sensor_imx179_mipi_raw.c \
                $(CUR_DIR)/sensor_imx219_mipi_raw.c \
                $(CUR_DIR)/sensor_hi544_mipi_raw.c \
                $(CUR_DIR)/sensor_ov5640_mipi.c \
                $(CUR_DIR)/sensor_autotest_ov5640_mipi_yuv.c \
                $(CUR_DIR)/sensor_ov5640.c \
                $(CUR_DIR)/sensor_autotest_ov5640_ccir_yuv.c \
                $(CUR_DIR)/sensor_autotest_ccir_yuv.c \
                $(CUR_DIR)/sensor_JX205_mipi_raw.c \
                $(CUR_DIR)/sensor_gc2035.c \
                $(CUR_DIR)/sensor_gc2155.c \
                $(CUR_DIR)/sensor_gc2155_mipi.c \
                $(CUR_DIR)/sensor_gc0308.c \
                $(CUR_DIR)/sensor_gc0310_mipi.c \
                $(CUR_DIR)/sensor_hm2058.c \
                $(CUR_DIR)/sensor_ov8865_mipi_raw.c \
                $(CUR_DIR)/sensor_gt2005.c \
                $(CUR_DIR)/sensor_hi702_ccir.c \
                $(CUR_DIR)/sensor_pattern.c \
                $(CUR_DIR)/sensor_ov7675.c\
                $(CUR_DIR)/sensor_hi253.c\
                $(CUR_DIR)/sensor_hi255.c\
                $(CUR_DIR)/sensor_s5k4ecgx_mipi.c \
                $(CUR_DIR)/sensor_sp2529_mipi.c \
                $(CUR_DIR)/sensor_s5k4ecgx.c \
                $(CUR_DIR)/sensor_sr352.c \
                $(CUR_DIR)/sensor_sr352_mipi.c \
                $(CUR_DIR)/sensor_sr030pc50_mipi.c \
                $(CUR_DIR)/sensor_s5k4h5yb_mipi_raw.c \
                $(CUR_DIR)/sensor_s5k5e3yx_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_ov5670_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_ov8858_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_ov2680_mipi_raw.c \
                $(CUR_DIR)/sensor_autotest_gc0310_mipi.c

LOCAL_SRC_FILES += \
                $(CUR_DIR)/oem/sensor_v1_cfg.c \
                $(CUR_DIR)/oem/sensor_v1_drv_u.c \
                $(CUR_DIR)/isp/isp_v1_param_file_update.c
endif

LOCAL_SHARED_LIBRARIES := libcutils libcamcommon
LOCAL_MODULE := libcamsensor
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)

