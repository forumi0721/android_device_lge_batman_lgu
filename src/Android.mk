ifneq ($(filter batman_lgu,$(TARGET_DEVICE)),)
	include $(all-subdir-makefiles)
endif
