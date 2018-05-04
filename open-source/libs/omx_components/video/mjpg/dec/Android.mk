LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_SRC_FILES := \
        SoftMJPG.cpp

LOCAL_C_INCLUDES := \
	$(TOP)/external/libjpeg-turbo \
        $(TOP)/frameworks/av/media/libmedia/include \
        $(TOP)/frameworks/av/media/libstagefright/include \
	$(TOP)/frameworks/av/media/libstagefright/omx/include/media/stagefright/omx \
	$(TOP)/vendor/sprd/open-source/libs/libstagefrighthw/include/openmax

LOCAL_CFLAGS := -DOSCL_EXPORT_REF= -DOSCL_IMPORT_REF=

LOCAL_SHARED_LIBRARIES := \
        libstagefright libstagefright_omx libstagefright_foundation libutils libdl liblog libmedia

LOCAL_MODULE := libstagefright_soft_mjpgdec
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)
