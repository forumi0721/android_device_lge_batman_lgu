# Configs
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/configs/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/prebuilt/configs/gps.conf:system/etc/gps.conf \
    $(LOCAL_PATH)/prebuilt/configs/vold.fstab:system/etc/vold.fstab \
    $(LOCAL_PATH)/prebuilt/configs/audio_effects.conf:system/etc/audio_effects.conf \
    $(LOCAL_PATH)/prebuilt/configs/media_profiles.xml:system/etc/media_profiles.xml \
    $(LOCAL_PATH)/prebuilt/configs/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/prebuilt/configs/batman_lgu-keypad.kl:system/usr/keylayout/batman_lgu-keypad.kl

$(call inherit-product, build/target/product/full.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)

#$(call inherit-product, device/common/gps/gps_us.mk)

$(call inherit-product-if-exists, vendor/lge/batman_lgu/batman_lgu-vendor.mk)

DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Ramdisk
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/root/init.batman_lgu.rc:root/init.batman_lgu.rc \
    $(LOCAL_PATH)/prebuilt/root/init.batman_lgu.usb.rc:root/init.batman_lgu.usb.rc \
    $(LOCAL_PATH)/prebuilt/root/ueventd.batman_lgu.rc:root/ueventd.batman_lgu.rc \
    $(LOCAL_PATH)/prebuilt/root/init.qcom.sh:root/init.qcom.sh

# bootlog
PRODUCT_COPY_FILES += \
    $(call add-to-product-copy-files-if-exists, $(LOCAL_PATH)/prebuilt/root/boot_logo_00000.rle:root/bootimages/boot_logo_00000.rle)

# Scripts
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.post_boot.sh:system/etc/init.qcom.post_boot.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.modem_links.sh:system/etc/init.qcom.modem_links.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.mdm_links.sh:system/etc/init.qcom.mdm_links.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.bt.sh:system/bin/init.qcom.bt.sh

# Camera lib
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/camera/camera.msm8660.so:system/lib/hw/camera.msm8660.so

# KoreanIME
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/ime/KoreanIME.apk:system/app/LatinIME.apk \
    $(LOCAL_PATH)/prebuilt/ime/libjni_koreanime.so:system/lib/libjni_koreanime.so

# Adreno200
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/jb_libs/egl/libGLESv2_adreno200.so:system/lib/egl/libGLESv2_adreno200.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/egl/libEGL_adreno200.so:system/lib/egl/libEGL_adreno200.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/egl/libGLESv1_CM_adreno200.so:system/lib/egl/libGLESv1_CM_adreno200.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/egl/libq3dtools_adreno200.so:system/lib/egl/libq3dtools_adreno200.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/egl/libGLESv2S3D_adreno200.so:system/lib/egl/libGLESv2S3D_adreno200.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/egl/eglsubAndroid.so:system/lib/egl/eglsubAndroid.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/lib/libC2D2.so:system/lib/libC2D2.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/lib/libsc-a2xx.so:system/lib/libsc-a2xx.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/lib/libc2d2_z180.so:system/lib/libc2d2_z180.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/lib/libOpenVG.so:system/lib/libOpenVG.so \
    $(LOCAL_PATH)/prebuilt/jb_libs/lib/libgsl.so:system/lib/libgsl.so

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.telephony.cdma.xml:system/etc/permissions/android.hardware.telephony.cdma.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml

# Device uses high-density artwork where available
PRODUCT_AAPT_CONFIG := normal hdpi xhdpi
PRODUCT_AAPT_PREF_CONFIG := xhdpi
PRODUCT_LOCALES += ko_KR

# Torch WifiDirect
PRODUCT_PACKAGES += \
    Torch \
    WifiDirect

# Audio
PRODUCT_PACKAGES += \
    audio.a2dp.default \
    audio.primary.msm8660 \
    audio_policy.msm8660 \
    libaudioutils

# Graphics
PRODUCT_PACKAGES += \
    copybit.msm8660 \
    gralloc.msm8660 \
    hwcomposer.msm8660 \
    libgenlock \
    libmemalloc \
    liboverlay \
    libQcomUI \
    libtilerenderer

# OMX
PRODUCT_PACKAGES += \
    libdivxdrmdecrypt \
    libI420colorconvert \
    libmm-omxcore \
    libOmxCore \
    libOmxVdec \
    libOmxVenc \
    libOmxAacEnc \
    libOmxAmrEnc \
    libstagefrighthw

# HDMI
PRODUCT_PACKAGES += \
    hdmid

# Torch
PRODUCT_PACKAGES += \
    Torch

# USB
PRODUCT_PACKAGES += \
    com.android.future.usb.accessory

# Filesystem management tools
PRODUCT_PACKAGES += \
    make_ext4fs \
    setup_fs

# Bluetooth
PRODUCT_PACKAGES += \
    brcm_patchram_plus

# GPS
PRODUCT_PACKAGES += \
    gps.batman_lgu

# NFC
# Commands to migrate prefs from com.android.nfc3 to com.android.nfc
PRODUCT_COPY_FILES += \
    $(call add-to-product-copy-files-if-exists, packages/apps/Nfc/migrate_nfc.txt:system/etc/updatecmds/migrate_nfc.txt)

PRODUCT_PACKAGES += \
    nfc.msm8660 \
    libnfc \
    libnfc_jni \
    Nfc \
    Tag \
    com.android.nfc_extras

# Bluetooth
PRODUCT_PACKAGES += \
    hcitool \
    hciconfig

## Local src
#PRODUCT_PACKAGES += \
#    hwaddrs \
#    ami304d \
#    power.batman_lgu \
#    lights.batman_lgu

# Prebuilt local src
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/local/hwaddrs:system/bin/hwaddrs \
    $(LOCAL_PATH)/prebuilt/local/ami304d:system/bin/ami304d \
    $(LOCAL_PATH)/prebuilt/local/audio.primary.batman_lgu.so:system/lib/hw/audio.primary.batman_lgu.so \
    $(LOCAL_PATH)/prebuilt/local/lights.batman_lgu.so:system/lib/hw/lights.batman_lgu.so \
    $(LOCAL_PATH)/prebuilt/local/power.batman_lgu.so:system/lib/hw/power.batman_lgu.so

PRODUCT_TAGS += \
    dalvik.gc.type-precise

$(call inherit-product-if-exists, device/lge/batman_lgu/stonecold/stonecold.mk)
