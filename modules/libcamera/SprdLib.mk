# add lib

# TARGET_BOARD_CAMERA_FACE_BEAUTY
ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libts_face_beautify_hal
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libts_face_beautify_hal.so
  LOCAL_MODULE_STEM_64 := libts_face_beautify_hal.so
  LOCAL_SRC_FILES_32 :=  arithmetic/facebeauty/libts_face_beautify_hal.so
  LOCAL_SRC_FILES_64 :=  arithmetic/facebeauty/libts_face_beautify_hal_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := arithmetic/facebeauty/libts_face_beautify_hal.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

# TARGET_BOARD_CAMERA_UV_DENOISE
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := libs/libuvdenoise.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

# TARGET_BOARD_CAMERA_Y_DENOISE
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := libs/libynoise.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

# TARGET_BOARD_CAMERA_SNR_UV_DENOISE
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := libs/libcnr.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

# TARGET_BOARD_CAMERA_HDR_CAPTURE
ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libsprd_easy_hdr
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libsprd_easy_hdr.so
  LOCAL_MODULE_STEM_64 := libsprd_easy_hdr.so
  LOCAL_SRC_FILES_32 :=  arithmetic/libsprd_easy_hdr.so
  LOCAL_SRC_FILES_64 :=  arithmetic/lib64/libsprd_easy_hdr.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := arithmetic/libsprd_easy_hdr.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif #end SPRD_LIB

# TARGET_BOARD_CAMERA_FACE_DETECT
# TARGET_BOARD_CAMERA_FD_LIB = omron
ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libeUdnDt
  LOCAL_MODULE_CLASS := STATIC_LIBRARIES
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libeUdnDt.a
  LOCAL_MODULE_STEM_64 := libeUdnDt.a
  LOCAL_SRC_FILES_32 := arithmetic/omron/lib32/libeUdnDt.a
  LOCAL_SRC_FILES_64 := arithmetic/omron/lib64/libeUdnDt.a
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)

  include $(CLEAR_VARS)
  LOCAL_MODULE := libeUdnCo
  LOCAL_MODULE_CLASS := STATIC_LIBRARIES
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libeUdnCo.a
  LOCAL_MODULE_STEM_64 := libeUdnCo.a
  LOCAL_SRC_FILES_32 := arithmetic/omron/lib32/libeUdnCo.a
  LOCAL_SRC_FILES_64 := arithmetic/omron/lib64/libeUdnCo.a
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_MODULE := libeUdnDt
  LOCAL_SRC_FILES := arithmetic/omron/lib32/libeUdnDt.a
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(PREBUILT_STATIC_LIBRARY)

  include $(CLEAR_VARS)
  LOCAL_MODULE := libeUdnCo
  LOCAL_SRC_FILES := arithmetic/omron/lib32/libeUdnCo.a
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(PREBUILT_STATIC_LIBRARY)

  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := arithmetic/omron/lib32/libeUdnDt.a
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)

  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := arithmetic/omron/lib32/libeUdnCo.a
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

# TARGET_BOARD_CAMERA_FACE_DETECT
# TARGET_BOARD_CAMERA_FD_LIB != omron
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := arithmetic/libface_finder.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

ifeq ($(strip $(ISP_HW_VER)),1.0)

# isp 1.0
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libae.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libawb.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libaf.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/liblsc.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libev.so
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)

else

#isp 2.0
ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libae
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libae.so
  LOCAL_MODULE_STEM_64 := libae.so
  LOCAL_SRC_FILES_32 :=  $(ISP_LIB_PATH)/lib/libae.so
  LOCAL_SRC_FILES_64 :=  $(ISP_LIB_PATH)/lib64/libae.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libae.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
 include $(CLEAR_VARS)
  LOCAL_MODULE := libawb
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libawb.so
  LOCAL_MODULE_STEM_64 := libawb.so
  LOCAL_SRC_FILES_32 :=  $(ISP_LIB_PATH)/lib/libawb.so
  LOCAL_SRC_FILES_64 :=  $(ISP_LIB_PATH)/lib64/libawb_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libawb.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libcalibration
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libcalibration.so
  LOCAL_MODULE_STEM_64 := libcalibration.so
  LOCAL_SRC_FILES_32 :=  $(ISP_LIB_PATH)/lib/libcalibration.so
  LOCAL_SRC_FILES_64 :=  $(ISP_LIB_PATH)/lib64/libcalibration_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libcalibration.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libAF
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libAF.so
  LOCAL_MODULE_STEM_64 := libAF.so
  LOCAL_SRC_FILES_32 :=  isp2.0/sft_af/lib/libAF.so
  LOCAL_SRC_FILES_64 :=  isp2.0/sft_af/lib/libAF_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := isp2.0/sft_af/lib/libAF.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libsft_af_ctrl
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libsft_af_ctrl.so
  LOCAL_MODULE_STEM_64 := libsft_af_ctrl.so
  LOCAL_SRC_FILES_32 :=  isp2.0/sft_af/lib/libsft_af_ctrl.so
  LOCAL_SRC_FILES_64 :=  isp2.0/sft_af/lib/libsft_af_ctrl_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := isp2.0/sft_af/lib/libsft_af_ctrl.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libaf_tune
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libaf_tune.so
  LOCAL_MODULE_STEM_64 := libaf_tune.so
  LOCAL_SRC_FILES_32 :=  isp2.0/sft_af/lib/libaf_tune.so
  LOCAL_SRC_FILES_64 :=  isp2.0/sft_af/lib/libaf_tune_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := isp2.0/sft_af/lib/libaf_tune.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libdeflicker
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libdeflicker.so
  LOCAL_MODULE_STEM_64 := libdeflicker.so
  LOCAL_SRC_FILES_32 := $(ISP_LIB_PATH)/lib/libdeflicker.so
  LOCAL_SRC_FILES_64 := $(ISP_LIB_PATH)/lib64/libdeflicker_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libdeflicker.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libspaf
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libspaf.so
  LOCAL_MODULE_STEM_64 := libspaf.so
  LOCAL_SRC_FILES_32 := $(ISP_LIB_PATH)/lib/libspaf.so
  LOCAL_SRC_FILES_64 := $(ISP_LIB_PATH)/lib64/libspaf_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/libspaf.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := liblsc
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := liblsc.so
  LOCAL_MODULE_STEM_64 := liblsc.so
  LOCAL_SRC_FILES_32 := $(ISP_LIB_PATH)/lib/liblsc.so
  LOCAL_SRC_FILES_64 := $(ISP_LIB_PATH)/lib64/liblsc_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
else
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := $(ISP_LIB_PATH)/lib/liblsc.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)		
  LOCAL_MODULE := libAl_Awb		
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES		
  LOCAL_MODULE_TAGS := optional		
  LOCAL_MULTILIB := both		
  LOCAL_MODULE_STEM_32 := libAl_Awb.so		
  LOCAL_MODULE_STEM_64 := libAl_Awb_64.so		
  LOCAL_SRC_FILES_32 := isp2.0/third_lib/alc_awb/libAl_Awb.so		
  LOCAL_SRC_FILES_64 := isp2.0/third_lib/alc_awb/libAl_Awb_64.so
  LOCAL_PROPRIETARY_MODULE := true	
  include $(BUILD_PREBUILT)		
else		
  include $(CLEAR_VARS)		
  LOCAL_PREBUILT_LIBS := isp2.0/third_lib/alc_awb/libAl_Awb.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)		
  LOCAL_MODULE := libAl_Awb_Sp		
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES		
  LOCAL_MODULE_TAGS := optional		
  LOCAL_MULTILIB := both		
  LOCAL_MODULE_STEM_32 := libAl_Awb_Sp.so		
  LOCAL_MODULE_STEM_64 := libAl_Awb_Sp_64.so		
  LOCAL_SRC_FILES_32 := isp2.0/third_lib/alc_awb/libAl_Awb_Sp.so		
  LOCAL_SRC_FILES_64 := isp2.0/third_lib/alc_awb/libAl_Awb_Sp_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)		
else		
  include $(CLEAR_VARS)		
  LOCAL_PREBUILT_LIBS := isp2.0/third_lib/alc_awb/libAl_Awb_Sp.so		
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)		
  LOCAL_MODULE := libaf_running		
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES		
  LOCAL_MODULE_TAGS := optional		
  LOCAL_MULTILIB := both		
  LOCAL_MODULE_STEM_32 := libaf_running.so		
  LOCAL_MODULE_STEM_64 := libaf_running.so		
  LOCAL_SRC_FILES_32 := isp2.0/third_lib/alc_af/lib/libaf_running.so		
  LOCAL_SRC_FILES_64 := isp2.0/third_lib/alc_af/lib/libaf_running_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)		
else		
  include $(CLEAR_VARS)		
  LOCAL_PREBUILT_LIBS := isp2.0/third_lib/alc_af/lib/libaf_running.so		
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm)
  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := isp2.0/alc_ip/ais/libAl_Ais.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)

  include $(CLEAR_VARS)
  LOCAL_PREBUILT_LIBS := isp2.0/alc_ip/ais/libAl_Ais_Sp.so
  LOCAL_MODULE_TAGS := optional
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_MULTI_PREBUILT)
endif

ifeq ($(strip $(TARGET_ARCH)),arm64)
  include $(CLEAR_VARS)
  LOCAL_MODULE := libAl_Ais
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libAl_Ais.so
  LOCAL_MODULE_STEM_64 := libAl_Ais.so
  LOCAL_SRC_FILES_32 :=  isp2.0/alc_ip/ais/libAl_Ais.so
  LOCAL_SRC_FILES_64 :=  isp2.0/alc_ip/ais/libAl_Ais_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)

  include $(CLEAR_VARS)
  LOCAL_MODULE := libAl_Ais_Sp
  LOCAL_MODULE_CLASS := SHARED_LIBRARIES
  LOCAL_MODULE_TAGS := optional
  LOCAL_MULTILIB := both
  LOCAL_MODULE_STEM_32 := libAl_Ais_Sp.so
  LOCAL_MODULE_STEM_64 := libAl_Ais_Sp.so
  LOCAL_SRC_FILES_32 :=  isp2.0/alc_ip/ais/libAl_Ais_Sp.so
  LOCAL_SRC_FILES_64 :=  isp2.0/alc_ip/ais/libAl_Ais_Sp_64.so
  LOCAL_PROPRIETARY_MODULE := true
  include $(BUILD_PREBUILT)
endif

endif

