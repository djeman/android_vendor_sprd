LOCAL_PATH := vendor/sprd/proprietaries

# Proprietaries drm
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/scx35l/system/etc/permissions/com.google.widevine.software.drm.xml:system/etc/permissions/com.google.widevine.software.drm.xml \
    $(LOCAL_PATH)/scx35l/system/framework/com.google.widevine.software.drm.jar:system/framework/com.google.widevine.software.drm.jar \
    $(LOCAL_PATH)/scx35l/system/vendor/lib/mediadrm/libwvdrmengine.so:system/vendor/lib/mediadrm/libwvdrmengine.so \
    $(LOCAL_PATH)/scx35l/system/vendor/lib/mediadrm/libdrmclearkeyplugin.so:system/vendor/lib/mediadrm/libdrmclearkeyplugin.so \
    $(LOCAL_PATH)/scx35l/system/vendor/lib/libwvdrm_L3.so:system/vendor/lib/libwvdrm_L3.so \
    $(LOCAL_PATH)/scx35l/system/vendor/lib/libWVStreamControlAPI_L3.so:system/vendor/lib/libWVStreamControlAPI_L3.so

# Proprietaries libomx
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_avcdec_hw_sprd.so:system/lib/libomx_avcdec_hw_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_avcdec_sw_sprd.so:system/lib/libomx_avcdec_sw_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_avcenc_hw_sprd.so:system/lib/libomx_avcenc_hw_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_m4vh263dec_hw_sprd.so:system/lib/libomx_m4vh263dec_hw_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_m4vh263dec_sw_sprd.so:system/lib/libomx_m4vh263dec_sw_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_m4vh263enc_hw_sprd.so:system/lib/libomx_m4vh263enc_hw_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_mp3dec_sprd.so:system/lib/libomx_mp3dec_sprd.so \
    $(LOCAL_PATH)/scx35l/system/lib/libomx_vpxdec_hw_sprd.so:system/lib/libomx_vpxdec_hw_sprd.so

