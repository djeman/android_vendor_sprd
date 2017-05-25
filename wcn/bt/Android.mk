#libbt is for the latest code.
#libbt_legacy is for older version.

LOCAL_PATH:= $(call my-dir)
ifneq ($(PLATFORM_VERSION),5.1)
    include $(LOCAL_PATH)/libbt/Android.mk \
            $(LOCAL_PATH)/hcidump/Android.mk
else
   include $(LOCAL_PATH)/libbt_legacy/Android.mk
endif
