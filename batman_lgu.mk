$(call inherit-product, build/target/product/full.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)

$(call inherit-product, device/common/gps/gps_us.mk)

$(call inherit-product-if-exists, vendor/lge/batman_lgu/batman_lgu-vendor.mk)

DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Ramdisk
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/root/init.batman_lgu.rc:root/init.batman_lgu.rc \
    $(LOCAL_PATH)/prebuilt/root/init.batman_lgu.usb.rc:root/init.batman_lgu.usb.rc \
    $(LOCAL_PATH)/prebuilt/root/ueventd.batman_lgu.rc:root/ueventd.batman_lgu.rc \
    $(LOCAL_PATH)/prebuilt/root/init.qcom.sh:root/init.qcom.sh

# Scripts
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.post_boot.sh:system/etc/init.qcom.post_boot.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.modem_links.sh:system/etc/init.qcom.modem_links.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.mdm_links.sh:system/etc/init.qcom.mdm_links.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.bt.sh:system/bin/init.qcom.bt.sh

# Configs
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/configs/media_profiles.xml:system/etc/media_profiles.xml \
    $(LOCAL_PATH)/prebuilt/configs/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/prebuilt/configs/audio_effects.conf:system/etc/audio_effects.conf \
    $(LOCAL_PATH)/prebuilt/configs/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/prebuilt/configs/vold.fstab:system/etc/vold.fstab

# Camera lib
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/camera/camera.msm8660.so:system/lib/hw/camera.msm8660.so

# Modules
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/kernel/ansi_cprng.ko:system/lib/modules/ansi_cprng.ko \
    $(LOCAL_PATH)/prebuilt/kernel/bthid.ko:system/lib/modules/bthid.ko \
    $(LOCAL_PATH)/prebuilt/kernel/cls_flow.ko:system/lib/modules/cls_flow.ko \
    $(LOCAL_PATH)/prebuilt/kernel/cpaccess.ko:system/lib/modules/cpaccess.ko \
    $(LOCAL_PATH)/prebuilt/kernel/dal_remotetest.ko:system/lib/modules/dal_remotetest.ko \
    $(LOCAL_PATH)/prebuilt/kernel/dma_test.ko:system/lib/modules/dma_test.ko \
    $(LOCAL_PATH)/prebuilt/kernel/evbug.ko:system/lib/modules/evbug.ko \
    $(LOCAL_PATH)/prebuilt/kernel/gspca_main.ko:system/lib/modules/gspca_main.ko \
    $(LOCAL_PATH)/prebuilt/kernel/ksapi.ko:system/lib/modules/ksapi.ko \
    $(LOCAL_PATH)/prebuilt/kernel/lcd.ko:system/lib/modules/lcd.ko \
    $(LOCAL_PATH)/prebuilt/kernel/max2165.ko:system/lib/modules/max2165.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mc44s803.ko:system/lib/modules/mc44s803.ko \
    $(LOCAL_PATH)/prebuilt/kernel/msm-buspm-dev.ko:system/lib/modules/msm-buspm-dev.ko \
    $(LOCAL_PATH)/prebuilt/kernel/msm_tsif.ko:system/lib/modules/msm_tsif.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mt2060.ko:system/lib/modules/mt2060.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mt20xx.ko:system/lib/modules/mt20xx.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mt2131.ko:system/lib/modules/mt2131.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mt2266.ko:system/lib/modules/mt2266.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mxl5005s.ko:system/lib/modules/mxl5005s.ko \
    $(LOCAL_PATH)/prebuilt/kernel/mxl5007t.ko:system/lib/modules/mxl5007t.ko \
    $(LOCAL_PATH)/prebuilt/kernel/oprofile.ko:system/lib/modules/oprofile.ko \
    $(LOCAL_PATH)/prebuilt/kernel/qt1010.ko:system/lib/modules/qt1010.ko \
    $(LOCAL_PATH)/prebuilt/kernel/sch_dsmark.ko:system/lib/modules/sch_dsmark.ko \
    $(LOCAL_PATH)/prebuilt/kernel/scsi_wait_scan.ko:system/lib/modules/scsi_wait_scan.ko \
    $(LOCAL_PATH)/prebuilt/kernel/spidev.ko:system/lib/modules/spidev.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tda18212.ko:system/lib/modules/tda18212.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tda18218.ko:system/lib/modules/tda18218.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tda18271.ko:system/lib/modules/tda18271.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tda827x.ko:system/lib/modules/tda827x.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tda8290.ko:system/lib/modules/tda8290.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tda9887.ko:system/lib/modules/tda9887.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tea5761.ko:system/lib/modules/tea5761.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tea5767.ko:system/lib/modules/tea5767.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tsif_chrdev.ko:system/lib/modules/tsif_chrdev.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tuner-simple.ko:system/lib/modules/tuner-simple.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tuner-types.ko:system/lib/modules/tuner-types.ko \
    $(LOCAL_PATH)/prebuilt/kernel/tuner-xc2028.ko:system/lib/modules/tuner-xc2028.ko \
    $(LOCAL_PATH)/prebuilt/kernel/xc5000.ko:system/lib/modules/xc5000.ko

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


# Permission files
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
PRODUCT_COPY_FILES += $(call add-to-product-copy-files-if-exists,\
packages/apps/Nfc/migrate_nfc.txt:system/etc/updatecmds/migrate_nfc.txt)

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
    hciconfig \
    hwaddrs

# batman_lguu source
PRODUCT_PACKAGES += \
    ami304d
#    power.batman_lgu \
#    lights.batman_lgu

ifeq ($(TARGET_PREBUILT_KERNEL),)
	LOCAL_KERNEL := $(LOCAL_PATH)/prebuilt/kernel/kernel
else
	LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

PRODUCT_COPY_FILES += \
    $(LOCAL_KERNEL):kernel \

PRODUCT_TAGS += dalvik.gc.type-precise

PRODUCT_BUILD_PROP_OVERRIDES += BUILD_UTC_DATE=1351143135
