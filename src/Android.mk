ifeq ($(TARGET_BOOTLOADER_BOARD_NAME),batman_lgu)
include $(call first-makefiles-under,$(call my-dir))
endif
