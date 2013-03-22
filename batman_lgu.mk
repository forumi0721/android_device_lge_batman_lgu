$(call inherit-product-if-exists, vendor/lge/batman_lgu/batman_lgu-vendor.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)

# The gps config appropriate for this device
PRODUCT_COPY_FILES += $(LOCAL_PATH)/prebuilt/configs/gps.conf:system/etc/gps.conf

PRODUCT_TAGS += dalvik.gc.type-precise
$(call inherit-product, frameworks/native/build/phone-xhdpi-1024-dalvik-heap.mk)

DEVICE_PACKAGE_OVERLAYS += device/lge/batman_lgu/overlay

# This device is xhdpi.  However the platform doesn't
# currently contain all of the bitmaps at xhdpi density so
# we do this little trick to fall back to the hdpi version
# if the xhdpi doesn't exist.
PRODUCT_AAPT_CONFIG := normal hdpi xhdpi
PRODUCT_AAPT_PREF_CONFIG := xhdpi
PRODUCT_LOCALES += ko_KR

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/configs/media_profiles.xml:system/etc/media_profiles.xml \
    $(LOCAL_PATH)/prebuilt/configs/media_codecs.xml:system/etc/media_codecs.xml

#$(call inherit-product, build/target/product/full.mk)
$(if $(wildcard device/lge/batman_lgu/stonecold/product/full.mk), $(call inherit-product-if-exists, device/lge/batman_lgu/stonecold/product/full.mk), $(call inherit-product, build/target/product/full.mk))

# root
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/root/init.batman_lgu.rc:root/init.batman_lgu.rc \
    $(LOCAL_PATH)/prebuilt/root/init.batman_lgu.usb.rc:root/init.batman_lgu.usb.rc \
    $(LOCAL_PATH)/prebuilt/root/ueventd.batman_lgu.rc:root/ueventd.batman_lgu.rc \
    $(LOCAL_PATH)/prebuilt/root/init.qcom.sh:root/init.qcom.sh

# bootlogo
PRODUCT_COPY_FILES += \
    $(call add-to-product-copy-files-if-exists, $(LOCAL_PATH)/prebuilt/root/boot_logo_00000.rle:root/bootimages/boot_logo_00000.rle)

# scripts
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.post_boot.sh:system/etc/init.qcom.post_boot.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.modem_links.sh:system/etc/init.qcom.modem_links.sh \
    $(LOCAL_PATH)/prebuilt/scripts/init.qcom.mdm_links.sh:system/etc/init.qcom.mdm_links.sh

# configs
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/configs/audio_policy.conf:system/vendor/etc/audio_policy.conf \
    $(LOCAL_PATH)/prebuilt/configs/MHLRCP.kl:system/usr/keylayout/MHLRCP.kl \
    $(LOCAL_PATH)/prebuilt/configs/atcmd_virtual_kbd.kl:system/usr/keylayout/atcmd_virtual_kbd.kl \
    $(LOCAL_PATH)/prebuilt/configs/ats_input.kl:system/usr/keylayout/ats_input.kl \
    $(LOCAL_PATH)/prebuilt/configs/batman_lgu-keypad.kl:system/usr/keylayout/batman_lgu-keypad.kl \
    $(LOCAL_PATH)/prebuilt/configs/melfas-ts.kl:system/usr/keylayout/melfas-ts.kl \
    $(LOCAL_PATH)/prebuilt/configs/osp-input.idc:system/usr/idc/osp-input.idc \
    $(LOCAL_PATH)/prebuilt/configs/osp-input.kl:system/usr/keylayout/osp-input.kl \
    $(LOCAL_PATH)/prebuilt/configs/pmic8xxx_pwrkey.kl:system/usr/keylayout/pmic8xxx_pwrkey.kl \
    $(LOCAL_PATH)/prebuilt/configs/synaptics_ts.kl:system/usr/keylayout/synaptics_ts.kl \
    $(LOCAL_PATH)/prebuilt/configs/synaptics_ts.idc:system/usr/idc/synaptics_ts.idc \
    $(LOCAL_PATH)/prebuilt/configs/synaptics_ts.kl:system/usr/keylayout/touch_dev.kl \
    $(LOCAL_PATH)/prebuilt/configs/synaptics_ts.idc:system/usr/idc/touch_dev.idc \
    $(LOCAL_PATH)/prebuilt/configs/vold.fstab:system/etc/vold.fstab

# camera lib
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/prebuilt/camera/camera.msm8660.so:system/lib/hw/camera.msm8660.so

# adreno 200 for JB 4.1
PRODUCT_COPY_FILES += \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/a225_pfp.fw:system/etc/firmware/a225_pfp.fw \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/a225_pm4.fw:system/etc/firmware/a225_pm4.fw \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/a225p5_pm4.fw:system/etc/firmware/a225p5_pm4.fw \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/leia_pfp_470.fw:system/etc/firmware/leia_pfp_470.fw \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/leia_pm4_470.fw:system/etc/firmware/leia_pm4_470.fw \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/yamato_pfp.fw:system/etc/firmware/yamato_pfp.fw \
     $(LOCAL_PATH)/prebuilt/adreno/etc/firmware/yamato_pm4.fw:system/etc/firmware/yamato_pm4.fw \
     $(LOCAL_PATH)/prebuilt/adreno/lib/egl/eglsubAndroid.so:system/lib/egl/eglsubAndroid.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/egl/libEGL_adreno200.so:system/lib/egl/libEGL_adreno200.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/egl/libGLESv1_CM_adreno200.so:system/lib/egl/libGLESv1_CM_adreno200.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/egl/libGLESv2S3D_adreno200.so:system/lib/egl/libGLESv2S3D_adreno200.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/egl/libGLESv2_adreno200.so:system/lib/egl/libGLESv2_adreno200.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/egl/libq3dtools_adreno200.so:system/lib/egl/libq3dtools_adreno200.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/libC2D2.so:system/lib/libC2D2.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/libOpenVG.so:system/lib/libOpenVG.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/libc2d2_z180.so:system/lib/libc2d2_z180.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/libgsl.so:system/lib/libgsl.so \
     $(LOCAL_PATH)/prebuilt/adreno/lib/libsc-a2xx.so:system/lib/libsc-a2xx.so

# KoreanIME
PRODUCT_COPY_FILES += \
    $(if $(wildcard device/lge/batman_lgu/stonecold/product/generic_no_telephony.mk), $(call add-to-product-copy-files-if-exists, $(LOCAL_PATH)/prebuilt/ime/KoreanIME.apk:system/app/KoreanIME.apk), $(call add-to-product-copy-files-if-exists, $(LOCAL_PATH)/prebuilt/ime/KoreanIME.apk:system/app/LatinIME.apk)) \
	$(call add-to-product-copy-files-if-exists, $(LOCAL_PATH)/prebuilt/ime/libjni_koreanime.so:system/lib/libjni_koreanime.so)

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

# audio
PRODUCT_PACKAGES += \
    audio.a2dp.default \
    audio.primary.msm8660 \
    audio_policy.msm8660 \
    libaudioutils

# graphics
PRODUCT_PACKAGES += \
    copybit.msm8660 \
    gralloc.msm8660 \
    hwcomposer.msm8660 \
    libgenlock \
    libmemalloc \
    liboverlay \
    libQcomUI \
    libtilerenderer

# omx
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

# hdmi
PRODUCT_PACKAGES += \
    hdmid

# usb
PRODUCT_PACKAGES += \
    com.android.future.usb.accessory

# filesystem management tools
PRODUCT_PACKAGES += \
    make_ext4fs \
    setup_fs

# bluetooth
PRODUCT_PACKAGES += \
    brcm_patchram_plus

# gps
PRODUCT_PACKAGES += \
    gps.batman_lgu

# nfc
PRODUCT_COPY_FILES += \
    $(call add-to-product-copy-files-if-exists, packages/apps/Nfc/migrate_nfc.txt:system/etc/updatecmds/migrate_nfc.txt)

PRODUCT_PACKAGES += \
    nfc.msm8660 \
    libnfc \
    libnfc_jni \
    Nfc \
    Tag \
    com.android.nfc_extras

# bluetooth
PRODUCT_PACKAGES += \
    hcitool \
    hciconfig

# torch, wifidirect
PRODUCT_PACKAGES += \
    Torch \
    WifiDirect

# local src
PRODUCT_PACKAGES += \
    ami304d \
    audio.primary.batman_lgu \
    hwaddrs \
    lights.batman_lgu \
    power.batman_lgu
