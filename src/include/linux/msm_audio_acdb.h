#ifndef __MSM_AUDIO_ACDB_H
#define __MSM_AUDIO_ACDB_H

#include <linux/msm_audio.h>

#define AUDIO_SET_VOCPROC_CAL		_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+0), unsigned)
#define AUDIO_SET_VOCPROC_STREAM_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+1), unsigned)
#define AUDIO_SET_VOCPROC_VOL_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+2), unsigned)
#define AUDIO_SET_AUDPROC_RX_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+3), unsigned)
#define AUDIO_SET_AUDPROC_RX_STREAM_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+4), unsigned)
#define AUDIO_SET_AUDPROC_RX_VOL_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+5), unsigned)
#define AUDIO_SET_AUDPROC_TX_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+6), unsigned)
#define AUDIO_SET_AUDPROC_TX_STREAM_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+7), unsigned)
#define AUDIO_SET_AUDPROC_TX_VOL_CAL	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+8), unsigned)
#define AUDIO_SET_SIDETONE_CAL		_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+9), unsigned)
#define AUDIO_SET_ANC_CAL		_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+10), unsigned)
#define AUDIO_SET_VOICE_RX_TOPOLOGY	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+11), unsigned)
#define AUDIO_SET_VOICE_TX_TOPOLOGY	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+12), unsigned)
#define AUDIO_SET_ADM_RX_TOPOLOGY	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+13), unsigned)
#define AUDIO_SET_ADM_TX_TOPOLOGY	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+14), unsigned)
#define AUDIO_SET_ASM_TOPOLOGY	_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+15), unsigned)
#define AUDIO_SET_AFE_TX_CAL		_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+16), unsigned)
#define AUDIO_SET_AFE_RX_CAL		_IOW(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+17), unsigned)


#define	AUDIO_MAX_ACDB_IOCTL	(AUDIO_MAX_COMMON_IOCTL_NUM+30)

/* ACDB structures */
struct cal_block {
	uint32_t	cal_size;	/* Size of Cal Data */
	uint32_t	cal_offset;	/* offset pointer to Cal Data */
};

struct sidetone_cal {
	uint16_t	enable;
	uint16_t	gain;
};

/* For Real-Time Audio Calibration */
#define AUDIO_GET_RTAC_ADM_INFO		_IOR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+1), unsigned)
#define AUDIO_GET_RTAC_VOICE_INFO	_IOR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+2), unsigned)
#define AUDIO_GET_RTAC_ADM_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+3), unsigned)
#define AUDIO_SET_RTAC_ADM_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+4), unsigned)
#define AUDIO_GET_RTAC_ASM_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+5), unsigned)
#define AUDIO_SET_RTAC_ASM_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+6), unsigned)
#define AUDIO_GET_RTAC_CVS_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+7), unsigned)
#define AUDIO_SET_RTAC_CVS_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+8), unsigned)
#define AUDIO_GET_RTAC_CVP_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+9), unsigned)
#define AUDIO_SET_RTAC_CVP_CAL	_IOWR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_ACDB_IOCTL+10), unsigned)
/* neo.kang  it should be removed. just temporal add for fixing compile error */
#define AUDIO_GET_RTAC_DEV_CTRL_INFO	_IOR(AUDIO_IOCTL_MAGIC, \
			(AUDIO_MAX_COMMON_IOCTL_NUM+26), unsigned)
#define	AUDIO_MAX_RTAC_IOCTL	(AUDIO_MAX_ACDB_IOCTL+20)

#endif /* __MSM_AUDIO_ACDB_H */
