## Specify phone tech before including full_phone
# LG U+ APN
PRODUCT_COPY_FILES += $(LOCAL_PATH)/prebuilt/configs/apns-conf.xml:system/etc/apns-conf.xml
PRODUCT_PACKAGES += Stk

# Release name
PRODUCT_RELEASE_NAME := OptimusVu

TARGET_BOOTANIMATION_NAME := vertical-720x1280

# Inherit some common CM stuff.
#$(call inherit-product, vendor/cm/config/common_full_phone.mk)
$(if $(wildcard device/lge/batman_lgu/stonecold/product/common_full_phone.mk), $(call inherit-product-if-exists, device/lge/batman_lgu/stonecold/product/common_full_phone.mk), $(call inherit-product, vendor/cm/config/common_full_phone.mk))

# Inherit device configuration
$(call inherit-product, device/lge/batman_lgu/batman_lgu.mk)

# Inherit some common StoneCold stuff
$(call inherit-product-if-exists, device/lge/batman_lgu/stonecold/stonecold.mk)

# Device naming
PRODUCT_DEVICE := batman_lgu
PRODUCT_NAME := cm_batman_lgu
PRODUCT_BRAND := LGE
PRODUCT_MODEL := LG-F100L
PRODUCT_MANUFACTURER := LGE
PRODUCT_DEFAULT_LANGUAGE := ko
PRODUCT_DEFAULT_REGION := KR

PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_UTC_DATE=1351143135 \
    PRODUCT_NAME=batman_lgu \
    BUILD_FINGERPRINT=LGE/batman_lgu/batman_lgu:4.0.4/IMM76D/LG-F100L-V29l.1c2da9957a:user/release-keys \
    PRIVATE_BUILD_DESC="batman_lgu-user 4.0.4 IMM76D 4822f9d0 release-keys" \
    TARGET_DEVICE=batman_lgu \
    TARGET_AAPT_CHARACTERISTICS=nosdcard \
    PRODUCT_DEFAULT_LANGUAGE=ko \
    PRODUCT_DEFAULT_REGION=KR
