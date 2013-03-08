/**************************************************************************
 +------------------------------------------------------------------------+
 | Desc.:   Test program for AMI306 Middleware (sysfs)                    |
 | File:	middletester.c                                            |
 | Release note:	                                                  |
 +------------------------------------------------------------------------+
 | Copyright (c) 2009 ~ 2010                                              |
 | AMIT Technology Inc.                                                   |
 | All rights reserved.                                                   |
 +------------------------------------------------------------------------+
 | This is source code in Software of AMIT 6-axis Middleware.             |
 | This software is the confidential and proprietary information of       |
 | AMIT Technology Inc.("Confidential Information")                       |
 | You shall not disclose such Confidential Information and shall         |
 | use it only in accordance with the terms of the license agreement.     |
 +------------------------------------------------------------------------+
 **************************************************************************/

#include <stdio.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <math.h>
#include "ami306.h"
#include "AMI_Middle.h"


#define LOG_TAG "AmitDaemon"
#include <cutils/log.h>

//#define QWERTY_OFFSET
#define ADC_WINDOW_CONTROL
#undef ACC_BMA250 

#define ACCURACY_RATE				0x10
#define POSTURE_ACCURACY_RATE			10
#define CONFIG_FILE_PATH		        "/data/amit/AMI306_Config2.ini"	//"/data/amit/AMI304_Config.ini"
#define VERIFIED_CODE	        0x0f0918	//for KR3DM:SA0=1
#define DISABLE_CALI				0
#define ENABLE_AUTO_CALI			1
#define ENABLE_SINGLE_CALI			2
#define DISABLE_ACC_CALI			0
#define ENABLE_ACC_CALI				1
#if defined(ADC_WINDOW_CONTROL)
#define ADC_WINDOW_NORMAL			0
#define ADC_WINDOW_CHANGED			1
#define ADC_WINDOW_EXCEEDED			2
#endif

#define AMI_WIN_RANGE		1800		/**< 1800 bit (ADC LSb) */
#define AMI_ABSD(x)		(fabs((x)))	/**< absolute value (double) */

#if defined(ACC_BMA250)
#define g_sensor_1g_gain_x 		256
#define g_sensor_1g_gain_y 		256
#define g_sensor_1g_gain_z 		256
#else
//                                                                       
//setting for KR3DH gain = 1024(1g) and offset = 2048
static int g_sensor_1g_gain_x = 1024;
static int g_sensor_1g_gain_y =	1024;
static int g_sensor_1g_gain_z = 1024;
#endif
#define g_sensor_offset_x 		2048
#define g_sensor_offset_y 		2048
#define g_sensor_offset_z 		2048
//setting for AMI304/306
#define m_sensor_gain_x 		600
#define m_sensor_gain_y 		600
#define m_sensor_gain_z 		600
#define m_sensor_offset_x 		2048
#define m_sensor_offset_y 		2048
#define m_sensor_offset_z 		2048

static int gfp = 0;
static int fpdaemon = 0;
static AMI_PARAMETER initParam;
static AMI_WIN_PARAMETER window;
static int accelerometer_8bit = 0;

#if defined(QWERTY_OFFSET)
static AMI_VECTOR3D	qwerty_close_m_offset;
static AMI_VECTOR3D	qwerty_open_m_offset;
#endif

#if !defined(ACC_BMA250)
#define KR3DM_IOCTL_BASE 77
/** The following define the IOCTL command values via the ioctl macros */
#define KR3DM_IOCTL_SET_DELAY       _IOW(KR3DM_IOCTL_BASE, 0, int)
#define KR3DM_IOCTL_GET_DELAY       _IOR(KR3DM_IOCTL_BASE, 1, int)
#define KR3DM_IOCTL_SET_ENABLE      _IOW(KR3DM_IOCTL_BASE, 2, int)
#define KR3DM_IOCTL_GET_ENABLE      _IOR(KR3DM_IOCTL_BASE, 3, int)
#define KR3DM_IOCTL_SET_G_RANGE     _IOW(KR3DM_IOCTL_BASE, 4, int)
#define KR3DM_IOCTL_READ_ACCEL_XYZ  _IOW(KR3DM_IOCTL_BASE, 22, int)
#endif

int WriteFileParameter(AMI_PARAMETER * param)
{
	FILE *fp = NULL;
	char temp[512];
	long code = VERIFIED_CODE;
	ami_sint8 wk_fine[3];	//20110418

	fp = fopen(CONFIG_FILE_PATH, "w+");	//setting file
	if (!fp) {
		//printf("open File failed\n");
		ALOGE("open File failed\n");
		return -1;
	}

	rewind(fp);

	sprintf(temp, "%ld\n", code);
	fprintf(fp,"%s", temp);
	fflush(fp);

	wk_fine[0] = wk_fine[1] = wk_fine[2] = 0;
	if(window.m_fine.x != window.m_0Gauss_fine.x)
		wk_fine[0] = window.m_fine.x;
	else
		wk_fine[0] = 0;
	if(window.m_fine.y != window.m_0Gauss_fine.y)
		wk_fine[1] = window.m_fine.y;
	else
		wk_fine[1] = 0;
	if(window.m_fine.z != window.m_0Gauss_fine.z)
		wk_fine[2] = window.m_fine.z;
	else
		wk_fine[2] = 0;

#if defined(QWERTY_OFFSET)
	//memset(temp, 0x00, sizeof(temp));
	sprintf(temp,"%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%ld",
		(param->a_gain.x/2),(param->a_gain.y/2),(param->a_gain.z/2),
		(param->a_offset.x - g_sensor_offset_x),(param->a_offset.y - g_sensor_offset_y),(param->a_offset.z - g_sensor_offset_z),
		(param->m_gain.x/ACCURACY_RATE),(param->m_gain.y/ACCURACY_RATE),(param->m_gain.z/ACCURACY_RATE),
		(param->m_offset.x/ACCURACY_RATE-m_sensor_offset_x),(param->m_offset.y/ACCURACY_RATE-m_sensor_offset_y),(param->m_offset.z/ACCURACY_RATE-m_sensor_offset_z),
		param->usr.a_offset.x,param->usr.a_offset.y,param->usr.a_offset.z, 
		qwerty_close_m_offset.x,qwerty_close_m_offset.y,qwerty_close_m_offset.z,
		qwerty_open_m_offset.x,qwerty_open_m_offset.y,qwerty_open_m_offset.z,
		param->gain_cor.x,param->gain_cor.y,param->gain_cor.z,
//20110418
		wk_fine[0],wk_fine[1],wk_fine[2],
		param->mag_radius);
#else
     //memset(temp, 0x00, sizeof(temp));
     sprintf(temp,"%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%ld",
		(param->a_gain.x/2),(param->a_gain.y/2),(param->a_gain.z/2),
		(param->a_offset.x - g_sensor_offset_x),(param->a_offset.y - g_sensor_offset_y),(param->a_offset.z - g_sensor_offset_z),
		(param->m_gain.x/ACCURACY_RATE),(param->m_gain.y/ACCURACY_RATE),(param->m_gain.z/ACCURACY_RATE),
		(param->m_offset.x/ACCURACY_RATE-m_sensor_offset_x),(param->m_offset.y/ACCURACY_RATE-m_sensor_offset_y),(param->m_offset.z/ACCURACY_RATE-m_sensor_offset_z),
		param->usr.a_offset.x,param->usr.a_offset.y,param->usr.a_offset.z, 
		param->usr.m_offset.x,param->usr.m_offset.y,param->usr.m_offset.z,
		param->gain_cor.x,param->gain_cor.y,param->gain_cor.z,
//20110418
		wk_fine[0],wk_fine[1],wk_fine[2],
		param->mag_radius);
#endif

	fprintf(fp,"%s", temp);
	fflush(fp);
	fclose(fp);

	return 0;
}

int ReadFileParameter(AMI_PARAMETER * param)
{
	FILE *fp = NULL;
#if defined(QWERTY_OFFSET)
	int data[27];
#else
	int data[24];
#endif
	signed long ldata[1];
	long code = VERIFIED_CODE;
	 int fscanfRet;

	fp = fopen(CONFIG_FILE_PATH, "r");	//Config file
	if (!fp) {
		//printf("open File failed\n");
		ALOGE("open File failed\n");
		return -1;
	}

	rewind(fp);

	fscanf(fp, "%ld\n", &ldata[0]);
	if (ldata[0] != code) {
		fclose(fp);
		return -2;
	}
#if defined(QWERTY_OFFSET)
	fscanfRet = fscanf(fp,"%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%ld",
		&data[0],&data[1],&data[2],
		&data[3],&data[4],&data[5],
		&data[6],&data[7],&data[8],
		&data[9],&data[10],&data[11],
		&data[12],&data[13],&data[14], 
		&data[15],&data[16],&data[17],
		&data[18],&data[19],&data[20],
		&data[21],&data[22],&data[23],
		&data[24],&data[25],&data[26],
		&ldata[0]);
		fclose(fp);

	if (fscanfRet != 28)	//if (fscanfRet != 25)	// the number of read data  = 22
	{
		ALOGE("Setting file format error!");
		return -3;
	}
#else
	fscanfRet = fscanf(fp,"%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%6d %6d %6d\n%ld",
			&data[0],&data[1],&data[2],
			&data[3],&data[4],&data[5],
			&data[6],&data[7],&data[8],
			&data[9],&data[10],&data[11],
			&data[12],&data[13],&data[14], 
			&data[15],&data[16],&data[17],
			&data[18],&data[19],&data[20],
			&data[21],&data[22],&data[23],
			&ldata[0]);
	fclose(fp);

	if (fscanfRet != 25){	//if (fscanfRet != 22) {	// the number of read data  = 22
		//printf("Setting file format error!");
		ALOGE("Setting file format error!");
		return -3;
	}
#endif
	//20110530 -------------------
	if((data[6]< 550 || data[6]>650) || (data[7]< 550 || data[7]>650) || (data[8]< 550 || data[8]>650))
		return -1;
	if(data[0]!=g_sensor_1g_gain_x || data[1]!=g_sensor_1g_gain_y || data[2]!=g_sensor_1g_gain_z)
		return -1;
	//<-------------------------
	param->a_gain.x = data[0]*2;
	param->a_gain.y = data[1]*2;
	param->a_gain.z = data[2]*2;
	param->a_offset.x = data[3] + g_sensor_offset_x;
	param->a_offset.y = data[4] + g_sensor_offset_y;
	param->a_offset.z = data[5] + g_sensor_offset_z;
	param->m_gain.x = data[6] * ACCURACY_RATE;
	param->m_gain.y = data[7] * ACCURACY_RATE;
	param->m_gain.z = data[8] * ACCURACY_RATE;
	param->m_offset.x = (data[9]  + m_sensor_offset_x) * ACCURACY_RATE;
	param->m_offset.y = (data[10] + m_sensor_offset_y) * ACCURACY_RATE;
	param->m_offset.z = (data[11] + m_sensor_offset_z) * ACCURACY_RATE;
	param->usr.a_offset.x = data[12];
	param->usr.a_offset.y = data[13];
	param->usr.a_offset.z = data[14];
#if defined(QWERTY_OFFSET)
	qwerty_close_m_offset.x = data[15];
	qwerty_close_m_offset.y = data[16];
	qwerty_close_m_offset.z = data[17];
	qwerty_open_m_offset.x = data[18];
	qwerty_open_m_offset.y = data[19];
	qwerty_open_m_offset.z = data[20];
	param->gain_cor.x = data[21];
	param->gain_cor.y = data[22];
	param->gain_cor.z = data[23];
	if(data[24]!=0)
		window.m_fine.x = data[24];
	if(data[25]!=0)
		window.m_fine.y = data[25];
	if(data[26]!=0)
		window.m_fine.z = data[26];
#else
	param->usr.m_offset.x = data[15];
	param->usr.m_offset.y = data[16];
	param->usr.m_offset.z = data[17];
	param->gain_cor.x = data[18];
	param->gain_cor.y = data[19];
	param->gain_cor.z = data[20];
	if(data[21]!=0)
		window.m_fine.x = data[21];
	if(data[22]!=0)
		window.m_fine.y = data[22];
	if(data[23]!=0)
		window.m_fine.z = data[23];
#endif
	param->mag_radius = ldata[0];

	return 0;
}

void MagCalibrationEnd(ami_uint8 result, ami_uint8 cont, AMI_PARAMETER *parm)
{
	int controlbyte[AMI306_CB_LENGTH];
	int res = 0;

	if(cont == 0x01) {
		return;
	}	
	
	if(0x00 == result) {
		if(fpdaemon != 0) {
			res = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_CONTROL, controlbyte);
			if(res != -1) {
				if(controlbyte[AMI306_CB_MAGCALI] == ENABLE_SINGLE_CALI) {
					controlbyte[AMI306_CB_MAGCALI] = DISABLE_CALI;
					ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CONTROL, controlbyte);
				}			
#if defined(QWERTY_OFFSET)
				if(controlbyte[AMI306_CB_QWERTY])
				{
					qwerty_open_m_offset.x = parm->usr.m_offset.x;
					qwerty_open_m_offset.y = parm->usr.m_offset.y;
					qwerty_open_m_offset.z = parm->usr.m_offset.z;
				}
				else
				{
					qwerty_close_m_offset.x = parm->usr.m_offset.x;
					qwerty_close_m_offset.y = parm->usr.m_offset.y;
					qwerty_close_m_offset.z = parm->usr.m_offset.z;
				}
#endif
			}
		}
		memcpy(&initParam, parm, sizeof(AMI_PARAMETER));
		WriteFileParameter(parm);

		ALOGI("Mag Calibration Success!\n");
	}
	else if(0x01 == result) {
	  	ALOGI("Mag Calibration Timeout!\n");
	}
	else {
	  	ALOGE("Mag Calibration Error!\n");		
	}
}

void AccCalibratoinEnd(ami_uint8 result, ami_uint8 cont, AMI_PARAMETER *parm)
{
	int controlbyte[AMI306_CB_LENGTH];
	int res = 0;

	if(cont == 0x01)
		return;

	if(0x00 == result) {
		if(fpdaemon != 0) {
			res = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_CONTROL, controlbyte);
			if(res != -1) {			
				controlbyte[AMI306_CB_ACCCALI] = DISABLE_ACC_CALI;
				ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CONTROL, controlbyte);
			}
		}
		WriteFileParameter(parm);
		ALOGI("AccCalibration Success!\n");
	}
	else if(0x01 == result) {
	  	ALOGI("AccCalibration Timeout!\n");
	}
	else {
	  	ALOGE("AccCalibration Error!\n");		
	}
}

int GSensorReadRawData(int* ax, int* ay, int* az)
{
	int ret = -1;
#if defined(ACC_BMA250)
	short buf[3];
#else
	int	buf[3];
#endif

	if (ax && ay && az)
		(*ax) = (*ay) = (*az) = 0;
	buf[0] = buf[1] = buf[2] = 0;

	if(gfp >= 0) {		
#if defined(ACC_BMA250)
		ret = ioctl(gfp, BMA250_READ_ACCEL_XYZ, buf);
#else
		ret = ioctl(gfp, KR3DM_IOCTL_READ_ACCEL_XYZ, buf);	//for KR3DM
#endif

		if (ret == -1) {
			ALOGE("Read from G-Sensor is error, read cnt(%d)\n",
			     ret);
		} 
		else {
			*ax = buf[0];
			*ay = buf[1];
			*az = buf[2];
			ret = 0;
		}
	}

	return ret;
}

int MSensorReadRawData(int* mx, int* my, int* mz)
{
//                                             
#if 1
    int   ret = -1;
    short buf[3];
    
    if((mx == NULL) || (my == NULL) || (mz == NULL))
    {
        ALOGE("Parameters have NULL!!\n");
        return -1;
    }

    if(fpdaemon >= 0) 
    {
        ret = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_SENSORDATA2, buf);
        
        if (ret == -1) 
        {
			ALOGE("Read from M-Sensor is error, read cnt(%d)\n", ret);
			return -1;
		}

		*mx = buf[0];
		*my = buf[1];
		*mz = buf[2];

		//ALOGE("Read from M-Sensor: %d %d %d\n", buf[0], buf[1], buf[2]);
		
		ret = 0;
    }

    return ret;
#else
	int ret = -1;
	char buf[22];	//20110630
	int 	mxh, mxl, myh, myl, mzh, mzl;

	if (mx && my && mz)
		(*mx) = (*my) = (*mz) = 0;
	mxh = mxl = myh = myl = mzh = mzl = 0;

	if( fpdaemon >= 0 ) {
		ret = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_SENSORDATA, buf);

		if (ret == -1) {
			ALOGE("Read from M-Sensor is error, read cnt(%d)\n", ret);
		}
		else {
		    sscanf(buf, "%x %x %x %x %x %x", &mxl, &mxh, &myl, &myh, &mzl, &mzh);	
		    *mx = mxh << 8 | mxl;
		    *my = myh << 8 | myl;
		    *mz = mzh << 8 | mzl;
			if (*mx>32768)  *mx = *mx-65536;//check negative value
			if (*my>32768)  *my = *my-65536;//check negative value
			if (*mz>32768)  *mz = *mz-65536;//check negative value
		    ret=0;
		}		
	}

	return ret;
#endif
//                                           
}	

void Set_Sleep(int sleep_time)
{
	if(sleep_time < 1)
		usleep(500);
	else if(sleep_time <= 20)
		usleep(sleep_time * 1000);  //control[0] * 1000 / 2 => sleep less 
	else if(sleep_time <= 60)
		usleep(sleep_time * 1000); 
	else if(sleep_time <= 200)
		usleep(sleep_time * 1000); 
	else
		usleep(sleep_time * 1000);  
}

void Set_Middleware_TimeOut(int sleep_time)
{
	int Check = 0;

	ALOGI("Set_Middleware_TimeOut: sleep_time=%d\n", sleep_time);
	
	if(sleep_time <= 5) {
#if !defined(STM_GYRO)	//20110630
		Check = AMI_SetIIRStrength(2,5);	// 0~100
#endif
		if (Check != 0)
		    ALOGE("The IIR filter parameter is invalid");
		
		Check = AMI_SetTimeout(2500);	// 300~30000
		if (Check != 0)
		ALOGE("The timeout parameter is invalid!");
	}
	else if(sleep_time <= 20) {
#if !defined(STM_GYRO)	//20110630
		Check = AMI_SetIIRStrength(1,3);	// 0~100
#endif
		if (Check != 0)
			ALOGE("The IIR filter parameter is invalid");
		
		Check = AMI_SetTimeout(600);
		if (Check != 0)
			ALOGE("The timeout parameter is invalid!");
	}	
	else if(sleep_time <= 60) {
#if !defined(STM_GYRO)	//20110630
		Check = AMI_SetIIRStrength(1,1);	
#endif
		if (Check != 0)
			ALOGE("The IIR filter parameter is invalid");
		
		Check = AMI_SetTimeout(333);	
		if (Check != 0)
			ALOGE("The timeout parameter is invalid!");  
	}
	else if(sleep_time <= 200) {
#if !defined(STM_GYRO)	//20110630
		Check = AMI_SetIIRStrength(0,0);
#endif
		if (Check != 0)
			ALOGE("The IIR filter parameter is invalid");
		
		Check = AMI_SetTimeout(300);	
		if (Check != 0)
			ALOGE("The timeout parameter is invalid!"); 
	}
	else { //other
#if !defined(STM_GYRO)	//20110630
		Check = AMI_SetIIRStrength(0,0);	// 0~100
#endif
		if (Check != 0)
			ALOGE("The IIR filter parameter is invalid");
		
		Check = AMI_SetTimeout(600);
		if (Check != 0)
			ALOGE("The timeout parameter is invalid!");
	}	
}

int CheckWindow(int mx, int my, int mz, int win_range)
{
	/*in case of over threshold, start window change */
	if((win_range < AMI_ABSD(mx)) || (win_range < AMI_ABSD(my)) || (win_range < AMI_ABSD(mz)))
	{
		ALOGI("~~ CheckWindow!! mx=%d, my=%d, mz=%d\n", mx, my, mz);
		if( AMI_OK == AMID_SearchOffset( &window ) )
		{
			/*window change notification */
			// ==== coase/fine x  ===============
			ALOGI("CheckWindow: m_coar.x=%d m_coar.y=%d m_coar.z=%d\n", window.m_coar.x, window.m_coar.y, window.m_coar.z);
			ALOGI("CheckWindow: m_fine.x=%d m_fine.y=%d m_fine.z=%d\n", window.m_fine.x, window.m_fine.y, window.m_fine.z);
			// === b0 ============== 
			ALOGI("CheckWindow: m_b0.x=%d m_b0.y=%d m_b0.z=%d\n", window.m_b0.x, window.m_b0.y, window.m_b0.z);
			// === delay ==============
			ALOGI("CheckWindow: m_delay.x=%d m_delay.y=%d m_delay.z=%d\n", window.m_delay.x, window.m_delay.y, window.m_delay.z);
			WriteFileParameter(&initParam);
			return 1;
		}
		else
		{
			ALOGE("Search Offset failed!!");
			return -1;
		}
	}
	return 0;
}

int init_AMITSensor()
{
//	int mx, my, mz;
	char cRet = 0;
	unsigned char ucRet = 0;
#if 1
	int controlbyte[AMI306_CB_LENGTH];
	int res = 0;
#endif
    

	memset((char *)&initParam, 0x00, sizeof(AMI_PARAMETER));
	memset((char *)&window, 0x00, sizeof(AMI_WIN_PARAMETER));

	//Please choose a number and set it to sensor direction by information below.
	//x means increasing direction of sensor x-axis. please check where is the sensor x-axis increasing direction when you see your device LCD.
	//y means increasing direction of sensor y-axis. please check where is the sensor y-axis increasing direction when you see your device LCD.
	//z means increasing direction of sensor z-axis. please check where is the sensor z-axis increasing direction when you see your device LCD.
	/* [0]  x:near to far y:down z:left */
	/* [1]  x:<- y:near to far z:down */
	/* [2]  x:down y:<- z:near to far */
	/* [3]  - */
	/* [4]  x:down y:far to near z:<- */
	/* [5]  x:far to near y:<- z:down */
	/* [6]  x:<- y:down z:far to near */
	/* [7]  - */
	/* [8]  x:up y:near to far z:<- */
	/* [9]  x:near to far y:<- z:up */
	/* [10] x:<- y:up z:near to far */
	/* [11] - */
	/* [12] x:far to near y:up z:<- */
	/* [13] x:<- y:far to near z:up */
	/* [14] x:up y:<- z:far to near */
	/* [15] - */
	/* [16] x:down y:near to far z:-> */
	/* [17] x:near to far y:-> z:down */
	/* [18] x:-> y:down z:near to far */
	/* [19] - */
	/* [20] x:far to near y:down z:-> */
	/* [21] x:-> y:far to near z:down */
	/* [22] x:down y:-> z:far to near */
	/* [23] - */
	/* [24] x:near to far y:up z:-> */
	/* [25] x:-> y:near to far z:up */
	/* [26] x:up y:-> z:near to far */
	/* [27] - */
	/* [28] x:up y:far to near z:-> */
	/* [29] x:far to near y:->z:up */
	/* [30] x:-> y:up z:far to near */

	if(fpdaemon != 0)
	{
		res = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_CONTROL, controlbyte);
		if(res != -1)
		{
			initParam.Mdir = controlbyte[AMI306_CB_MDIR];
		}
		else
		{
	initParam.Mdir = 10;
		
		}
	}
	initParam.Gdir = 30;
	//    initParam.sensor_type = AMI_SENSOR_MODE2;	//AMI306
	initParam.sensor_type = AMI_SENSOR_MODE3;	//AMI306

	AMID_GetCal(&initParam, &window);
	// == fine_output ==========
	ALOGI("AMID_GetCal: m_fine_output.x=%d m_fine_output.y=%d m_fine_output.z=%d\n", window.m_fine_output.x, window.m_fine_output.y, window.m_fine_output.z);

	// == gain =================
	ALOGI("AMID_GetCal: m_gain.x=%d m_gain.y=%d m_gain.z=%d\n", initParam.m_gain.x, initParam.m_gain.y, initParam.m_gain.z);

	// gain_para ===============
	ALOGI("AMID_GetCal: gain_para_XY=%d gain_para_XZ=%d gain_para_YX=%d\n", initParam.gain_para_XY, initParam.gain_para_XZ, initParam.gain_para_YX);
	ALOGI("AMID_GetCal: gain_para_YZ=%d gain_para_ZX=%d gain_para_ZY=%d\n", initParam.gain_para_YZ, initParam.gain_para_ZX, initParam.gain_para_ZY);

	// ==== coase/fine x  ===============
	ALOGI("AMID_GetCal: m_coar.x=%d m_coar.y=%d m_coar.z=%d\n", window.m_coar.x, window.m_coar.y, window.m_coar.z);
	ALOGI("AMID_GetCal: m_0Gauss_coar.x=%d m_0Gauss_coar.y=%d m_0Gauss_coar.z=%d\n", window.m_0Gauss_coar.x, window.m_0Gauss_coar.y, window.m_0Gauss_coar.z);
	ALOGI("AMID_GetCal: m_fine.x=%d m_fine.y=%d m_fine.z=%d\n", window.m_fine.x, window.m_fine.y, window.m_fine.z);
	ALOGI("AMID_GetCal: m_0Gauss_fine.x=%d m_0Gauss_fine.y=%d m_0Gauss_fine.z=%d\n", window.m_0Gauss_fine.x, window.m_0Gauss_fine.y, window.m_0Gauss_fine.z);

	// === b0 ============== 
	ALOGI("AMID_GetCal: m_b0.x=%d m_b0.y=%d m_b0.z=%d\n", window.m_b0.x, window.m_b0.y, window.m_b0.z);

	// === delay ==============
	ALOGI("AMID_GetCal: m_delay.x=%d m_delay.y=%d m_delay.z=%d\n", window.m_delay.x, window.m_delay.y, window.m_delay.z);

//	MSensorReadRawData(&mx, &my, &mz);
//	if(CheckWindow(mx, my, mz, (AMI_WIN_RANGE))) {
//		ALOGI("Window changed!!");
//	}
	   
	
	// read sensor calibration value
	if( ReadFileParameter(&initParam) < 0 ) { //read config file, if no,use default

		initParam.a_gain.x = g_sensor_1g_gain_x * 2; 
		initParam.a_gain.y = g_sensor_1g_gain_y * 2;
		initParam.a_gain.z = g_sensor_1g_gain_z * 2;
		//for middleware use g-offset = 2048		
		initParam.a_offset.x = 2048;    
		initParam.a_offset.y = 2048;   	
		initParam.a_offset.z = 2048;
		//Magnetic gain setting
		if(initParam.m_gain.x)
			initParam.m_gain.x = initParam.m_gain.x * ACCURACY_RATE;      	
		else
			initParam.m_gain.x = m_sensor_gain_x * ACCURACY_RATE;
		if(initParam.m_gain.y)
			initParam.m_gain.y = initParam.m_gain.y * ACCURACY_RATE;      	
		else
			initParam.m_gain.y = m_sensor_gain_y * ACCURACY_RATE;
		if(initParam.m_gain.z)
			initParam.m_gain.z = initParam.m_gain.z * ACCURACY_RATE;      	
		else
			initParam.m_gain.z = m_sensor_gain_z * ACCURACY_RATE;
			//for middleware use m-offset = 2048
		initParam.m_offset.x = 2048 * ACCURACY_RATE;   	
		initParam.m_offset.y = 2048 * ACCURACY_RATE;   	
		initParam.m_offset.z = 2048 * ACCURACY_RATE;
		//user offset for accelerometer
		initParam.usr.a_offset.x = 0;  
		initParam.usr.a_offset.y = 0;  
		initParam.usr.a_offset.z = 0;
		//user offset for ami304/306
		initParam.usr.m_offset.x = 0;  
		initParam.usr.m_offset.y = 0;  
		initParam.usr.m_offset.z = 0;
#if defined(QWERTY_OFFSET)
		qwerty_close_m_offset.x = 0;
		qwerty_close_m_offset.y = 0;
		qwerty_close_m_offset.z = 0;
		qwerty_open_m_offset.x = 0;
		qwerty_open_m_offset.y = 0;
		qwerty_open_m_offset.z = 0;
#endif
		initParam.gain_cor.x = 100;
		initParam.gain_cor.y = 100;
		initParam.gain_cor.z = 100;
		      
		initParam.mag_radius = 0;            
		   
		WriteFileParameter(&initParam); //write out to default config file
	}	
	
#if defined(QWERTY_OFFSET)
	if(fpdaemon != 0)
	{
		res = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_CONTROL, controlbyte);
		if(res != -1)
		{
			if(controlbyte[AMI306_CB_QWERTY])
			{
				initParam.usr.m_offset.x = qwerty_open_m_offset.x;
				initParam.usr.m_offset.y = qwerty_open_m_offset.y;
				initParam.usr.m_offset.z = qwerty_open_m_offset.z;
			}
			else
			{
				initParam.usr.m_offset.x = qwerty_close_m_offset.x;
				initParam.usr.m_offset.y = qwerty_close_m_offset.y;
				initParam.usr.m_offset.z = qwerty_close_m_offset.z;
			}
		}
	}
#endif
	cRet = AMI_InitializeSensor(&initParam);
	if( cRet != 0) { //return value is not "0", please contact with AMIT
		//ALOGE("Internal Error!error code:%d, please contact with vendor!", cRet);
		//need test    	return -1;
		AMIL_InitSensor(&initParam);
	}

	cRet = AMI_SetIIRStrength(1,0);	// 0~100
	if (cRet != 0)
		ALOGE("The IIR filter parameter is invalid");
		
	ucRet = AMI_SetTimeout(600);	// 300~30000
	if (ucRet != 0)
		ALOGE("The timeout parameter is invalid!");

	ALOGI("Start to Auto-Calibration!!!");
	ucRet = AMI_CalibrationStart(MagCalibrationEnd);
	if (ucRet != 0)
		ALOGE("AMI_CalibrationStart Error!");   	

	return 0;
}

int I2c_Read(ami_uint8 reg_adr, ami_uint8 * buf, ami_uint8 buf_len)
{
	int 	ret = -1;
	char	i2c_buf[64];
	int	i;

	if( fpdaemon >= 0 ) {
		memset(i2c_buf, 0x00, 64);
		i2c_buf[0] = reg_adr;
		i2c_buf[1] = buf_len;
		
		ret = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_I2CADDR, i2c_buf);
		if(ret == -1 ) {
			ALOGE("Set I2c Addr error, read cnt(%d)\n", ret);
			return -1;
		}
//		ALOGI("I2c_Read : reg_adr=0x%x, buf_len=%d\n", reg_adr, buf_len);

		ret = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_I2CDATA, buf);
		if(ret == -1 ) {
			ALOGE("Get I2c Data error, read cnt(%d)\n", ret);
			return -1;
		}
//		ALOGI("I2c_Read : buf[0]=0x%x, buf[1]=0x%x, buf[2]=0x%x, buf[3]=0x%x, buf[4]=0x%x, buf[5]=0x%x, buf[6]=0x%x, buf[7]=0x%x\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	}
	return 0;
}

int I2c_Write(ami_uint8 reg_adr, ami_uint8 * buf, ami_uint8 buf_len)
{
	int 	ret = -1;
	char	i2c_buf[64];
	int	i;

	if (fpdaemon >= 0) {
		memset(i2c_buf, 0x00, 64);
		i2c_buf[0] = reg_adr;
		i2c_buf[1] = buf_len;
		
		for (i=0; i<buf_len; i++) {
			i2c_buf[i+2] = buf[i];
		}
		ret = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_I2CDATA, i2c_buf);

		if (ret == -1 ) {
			ALOGE("Set I2c Data error, read cnt(%d)\n", ret);
			return -1;
		}
		//ALOGI("I2c_Write : reg_adr=0x%x, buf_len=%d\n", reg_adr, buf_len);
	}
	return 0;
}

int main()
{
	int control[AMI306_CB_LENGTH];
	int mx,my,mz,ax,ay,az;	
	int res = 0;	
	AMI_SENSORVALUE val;
	AMI_MOTION info;	
	int iYaw, iRoll, iPitch, iStatus;
	int raw_mx,raw_my,raw_mz,raw_ax,raw_ay,raw_az;
	int posturebuf[4];
#if defined(STM_GYRO)	//20110630
	int calidata[4];
#else
	int calidata[7];
#endif
	int control_set_timeout  =  0;
#if defined(QWERTY_OFFSET)
	int control_qwerty= 0;
#endif
	int mag_cali_flag = ENABLE_AUTO_CALI;
   	ami_uint8 check_error;	
   	int iRet = 0;   	
	int en_report = 1;
	ami_sint8 wk_fine[3];	//20110222
	ami_sint8 wk_coar[3];	//20110222


	ALOGI("AMI306+BMA250 Middleware Tester (daemon), Version:3.0.55.64\n");
	ALOGI("Copyright (c) 2010 all rights preserved by AMIT Technology Inc.\n");

#if defined(ACC_BMA250)
	gfp = open("/dev/bma250", O_RDWR);
#else
	//gfp = open("/dev/KR3DH", O_RDWR);
	gfp = open("/dev/k3dh_acc_misc", O_RDWR);
#endif

	if (gfp < 0) {
	    	gfp = open("/dev/KR3DM", O_RDWR);
	    	if (gfp < 0) {
			ALOGE("Cannot open Accelerometer!!!\n");
			return -1;
	    	}
		else {
			// 8bit accelerometer
			ALOGI("8bit accelerometer\n");
			g_sensor_1g_gain_x = 64;
			g_sensor_1g_gain_y = 64;
			g_sensor_1g_gain_z = 64;
		}
    	}

	fpdaemon = open("/dev/ami306daemon", O_RDWR);
	if (fpdaemon == -1) {
		close(gfp);
		ALOGE("Cannot open ami306daemon!!!\n");
		return -1;
	}
  
	iRet = init_AMITSensor();	
	if( iRet==-1 )
	{
		return -2;	
	}
	
	//20110418
	if(((window.m_fine.x != window.m_0Gauss_fine.x)||(window.m_fine.y != window.m_0Gauss_fine.y)||(window.m_fine.z != window.m_0Gauss_fine.z)) && (initParam.sensor_type == AMI_SENSOR_MODE3))
	{
		wk_coar[0] = (ami_uint8)window.m_coar.x;
		wk_coar[1] = (ami_uint8)window.m_coar.y;
		wk_coar[2] = (ami_uint8)window.m_coar.z;
		
		wk_fine[0] = (ami_uint8)window.m_fine.x;
		wk_fine[1] = (ami_uint8)window.m_fine.y;
		wk_fine[2] = (ami_uint8)window.m_fine.z;

//20110531		AMID_SetOffset((ami_uint8*)&wk_coar,(ami_uint8*)&wk_fine);
	}
	
	//start do-while >>
	do {
		res = ioctl(fpdaemon, AMI306DAE_IOCTL_GET_CONTROL, control);
		if (res < 0) {
			control[AMI306_CB_LOOPDELAY] = 20;
			control[AMI306_CB_RUN] = 1;
			control[AMI306_CB_ACTIVESENSORS] = 0;
#if defined(QWERTY_OFFSET)
			control[AMI306_CB_QWERTY] = 0;
#endif
		}

		//no sensor
		if( control[AMI306_CB_ACTIVESENSORS] == 0 ) {
			usleep(1000000);
			continue;		
		}
		
//20110222
		if((control[AMI306_CB_RUN] == 2) && (control[AMI306_CB_CHANGE_WINDOW] != ADC_WINDOW_NORMAL))
		{
			wk_coar[0] = (ami_uint8)window.m_coar.x;
			wk_coar[1] = (ami_uint8)window.m_coar.y;
			wk_coar[2] = (ami_uint8)window.m_coar.z;
			
			wk_fine[0] = (ami_uint8)window.m_fine.x;
			wk_fine[1] = (ami_uint8)window.m_fine.y;
			wk_fine[2] = (ami_uint8)window.m_fine.z;

//20110531			AMID_SetOffset((ami_uint8*)&wk_coar,(ami_uint8*)&wk_fine);
			control[AMI306_CB_RUN] = 1;
			ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CONTROL, control);
		}
		else if((control[AMI306_CB_RUN] == 2) && (control[AMI306_CB_CHANGE_WINDOW] == ADC_WINDOW_NORMAL))
		{
			control[AMI306_CB_RUN] = 1;
			ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CONTROL, control);
		}
		
#if defined(QWERTY_OFFSET)
		if(control_qwerty != control[AMI306_CB_QWERTY])
		{
			if(control[AMI306_CB_QWERTY])
			{
				initParam.usr.m_offset.x = qwerty_open_m_offset.x;
				initParam.usr.m_offset.y = qwerty_open_m_offset.y;
				initParam.usr.m_offset.z = qwerty_open_m_offset.z;
			}
			else
			{
				initParam.usr.m_offset.x = qwerty_close_m_offset.x;
				initParam.usr.m_offset.y = qwerty_close_m_offset.y;
				initParam.usr.m_offset.z = qwerty_close_m_offset.z;
			}
			AMI_CalibrationCancel();
			if( AMI_InitializeSensor(&initParam) != 0) //return value is not "0", please contact with AMIT
			{
				ALOGE("Internal Error! please contact with vendor!");
				//test					return -1;
				AMIL_InitSensor(&initParam);
			}
			AMI_CalibrationStart(MagCalibrationEnd);
			control_qwerty = control[AMI306_CB_QWERTY];
		}
#endif
		mx = my = mz = ax = ay = az = 0;
		//                                            
		//   not used the Gyroscope
		//  (control[AMI306_CB_ACTIVESENSORS] & AMIT_BIT_GYROSCOPE) 
		//orientation, magnetic_field
		if( (control[AMI306_CB_ACTIVESENSORS] & AMIT_BIT_ORIENTATION) || 
		    (control[AMI306_CB_ACTIVESENSORS] & AMIT_BIT_MAGNETIC_FIELD) ) {
			MSensorReadRawData(&mx, &my, &mz);

			res = CheckWindow(mx, my, mz, AMI_WIN_RANGE);
			if(res == 1)
			{
#if defined(ADC_WINDOW_CONTROL)
				if(control[AMI306_CB_CHANGE_WINDOW] == ADC_WINDOW_NORMAL)
					control[AMI306_CB_CHANGE_WINDOW] = ADC_WINDOW_CHANGED;
				ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CONTROL, control);
#endif
				AMI_CalibrationCancel();
				if( AMI_InitializeSensor(&initParam) != 0) { //return value is not "0", please contact with AMIT
					//ALOGE("Internal Error! please contact with vendor!");
					//need test    	return -1;
					AMIL_InitSensor(&initParam);
				}

				Set_Middleware_TimeOut(control[AMI306_CB_LOOPDELAY]);
				AMI_CalibrationStart(MagCalibrationEnd);
				Set_Sleep(control[AMI306_CB_LOOPDELAY]);
				continue;
			}
#if defined(ADC_WINDOW_CONTROL)
			else if (res < 0)
			{
				control[AMI306_CB_CHANGE_WINDOW] = ADC_WINDOW_EXCEEDED;
				ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CONTROL, control);
			}
#endif
		}              
		
		//orientation, accelerometer
		if( (control[AMI306_CB_ACTIVESENSORS] & AMIT_BIT_ORIENTATION) ||
		    (control[AMI306_CB_ACTIVESENSORS] & AMIT_BIT_ACCELEROMETER) ||
		    (control[AMI306_CB_ACTIVESENSORS] & AMIT_BIT_PEDOMETER) ) {
			GSensorReadRawData(&ax, &ay, &az);
		}	

		if(mag_cali_flag != control[AMI306_CB_MAGCALI]) {
			if(control[AMI306_CB_MAGCALI] == ENABLE_AUTO_CALI ||
			   control[AMI306_CB_MAGCALI] == ENABLE_SINGLE_CALI)
				AMI_CalibrationStart(MagCalibrationEnd);
			else
				AMI_CalibrationCancel();
               
			mag_cali_flag = control[AMI306_CB_MAGCALI];					
		}

		//for acc calibration
		if(control[AMI306_CB_ACCCALI] == ENABLE_ACC_CALI)
		{
			AMI_AccCalibrationStart(AccCalibratoinEnd);
		}	
			
		mx += m_sensor_offset_x;
		mx *= ACCURACY_RATE;
		my += m_sensor_offset_y;
		my *= ACCURACY_RATE;
		mz += m_sensor_offset_z;
		mz *= ACCURACY_RATE; 

		ax += g_sensor_offset_x; 
		ay += g_sensor_offset_y; 
		az += g_sensor_offset_z; 		
		
		val.mx = mx;
		val.my = my;
		val.mz = mz;
		val.ax = ax;
		val.ay = ay;
		val.az = az;
        
		check_error = AMI_InputSensorValue(val);
		if(check_error != 0) {
		    ALOGE("AMI_InputSensorValue Error!!! \n");
		    continue;		
		}
			
		AMI_GetMotionInfoLatest(&info);  
#if !defined(STM_GYRO)	//20110630
		iStatus = (int) AMI_CheckMagneticInterference();
		iRoll =   (int)(/*CONVBIT2DEG*/(info.Android_roll)*POSTURE_ACCURACY_RATE);
		iYaw =    (int)(CONVBIT2DEG(info.Android_yaw)*POSTURE_ACCURACY_RATE);
		iPitch =  (int)(/*CONVBIT2DEG*/(info.Android_pitch)*POSTURE_ACCURACY_RATE);			
#endif
		//                                           
		// multiplied by POSTURE_ACCURACY_RATE
		raw_mx = (int) (-info.mag_mGauss.x * POSTURE_ACCURACY_RATE);
		raw_my = (int) (-info.mag_mGauss.y * POSTURE_ACCURACY_RATE);
		raw_mz = (int) (-info.mag_mGauss.z * POSTURE_ACCURACY_RATE);
#if !defined(STM_GYRO)	//20110630
		raw_ax = (int) (info.acc_mg.x * POSTURE_ACCURACY_RATE);
		raw_ay = (int) (info.acc_mg.y * POSTURE_ACCURACY_RATE);
		raw_az = (int) (info.acc_mg.z * POSTURE_ACCURACY_RATE);
			
		posturebuf[0] = iYaw;
		posturebuf[1] = iPitch;
		posturebuf[2] = iRoll;
		posturebuf[3] = iStatus;
		res = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_POSTURE, posturebuf);
			
		if( res < 0 ) {  
		    posturebuf[0] = posturebuf[1] = posturebuf[2] = posturebuf[3] = 0;
		    res = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_POSTURE, posturebuf);		
		}
#endif

		calidata[0] = raw_mx;
		calidata[1] = raw_my; 
		calidata[2] = raw_mz;
#if defined(STM_GYRO)	//20110630
		calidata[3] = iStatus;
#else
		calidata[3] = raw_ax;
		calidata[4] = raw_ay;
		calidata[5] = raw_az;
		calidata[6] = iStatus;
#endif
			
		res = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CALIDATA, calidata);
			
		if( res < 0 ) {
			memset(calidata, 0, sizeof(calidata));
			res = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_CALIDATA, calidata);		
		}		                        

		res = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_REPORT, &en_report); 
		if (res < 0) {
			en_report = 1;
			res = ioctl(fpdaemon, AMI306DAE_IOCTL_SET_REPORT, &en_report); 
		}
				
		if(control_set_timeout != control[AMI306_CB_LOOPDELAY]) {
			Set_Middleware_TimeOut(control[AMI306_CB_LOOPDELAY]);
			control_set_timeout = control[AMI306_CB_LOOPDELAY];
		}

		Set_Sleep(control[AMI306_CB_LOOPDELAY]);		

	} while (control[AMI306_CB_RUN] != 0);  //20110222
	//End do-while <<

	//printf("Job finished!!\n");
	ALOGI("Job finished!!\n");

	close(gfp);
	close(fpdaemon);

	return 0;
}
