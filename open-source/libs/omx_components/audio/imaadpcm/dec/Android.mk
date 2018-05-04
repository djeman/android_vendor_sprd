LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        SoftIMAADPCM.cpp

LOCAL_C_INCLUDES := \
        $(TOP)/frameworks/av/media/libstagefright/include \
	$(TOP)/frameworks/av/media/libstagefright/omx/include/media/stagefright/omx \
	$(TOP)/vendor/sprd/open-source/libs/libstagefrighthw/include/openmax

LOCAL_SHARED_LIBRARIES := \
        libstagefright libstagefright_omx libstagefright_foundation libutils liblog libmedia

LOCAL_MODULE := libstagefright_soft_imaadpcmdec
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)
