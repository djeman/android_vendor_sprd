#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/kernel.h>
#include <linux/magic.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/vfs.h>
#include <sys/mman.h>
#include <linux/ioctl.h>
#include <linux/time.h>
#include <cutils/log.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include"fmtest.h"

#define AUDCTL "/dev/pipe/mmi.audio.ctrl"

int SendAudioTestCmd(const unsigned char * cmd,int bytes);
int fm_open(void);
static int fm_close(void);
static int fm_tune(unsigned short set_freq);
static int fm_seekup(unsigned char direction);

static int fm_fd = -1;

int SendAudioTestCmd(const unsigned char * cmd,int bytes)
{
    int fd = -1;
    int ret=-1;
    int bytes_to_read = bytes;

    if(cmd==NULL){
        return -1;
    }

    if(fd < 0) {
        fd = open(AUDCTL, O_WRONLY | O_NONBLOCK);
    }

    if(fd < 0) {
        return -1;
    }else{
        do {
            ret = write(fd, cmd, bytes);
            if( ret > 0) {
                if(ret <= bytes) {
                    bytes -= ret;
                }
            }
            else if((!((errno == EAGAIN) || (errno == EINTR))) || (0 == ret)) {
                ALOGE("pipe write error %d,bytes read is %d",errno,bytes_to_read - bytes);
                break;
            }
            else {
                ALOGW("pipe_write_warning: %d,ret is %d",errno,ret);
            }
        }while(bytes);
    }

    if(fd > 0) {
        close(fd);
    }

    if(bytes == bytes_to_read)
        return ret ;
    else
        return (bytes_to_read - bytes);
}


static int fm_open_dev(void)
{
	 fm_fd = open("/dev/fm", O_RDONLY | O_NONBLOCK);
	 if (fm_fd < 0) {
		 printf("FM open faile! errno[%d] = %s", errno, strerror(errno));
		 return -1;
	 }

	 printf("FM open success ! fd = %d\n", fm_fd);
	 return 0;
}

static int fm_close_dev(void)
{
	int ret = 0;
	 ret = close(fm_fd);
	 if (0 != ret) {
		 printf("FM close faile! errno[%d] = %s", errno, strerror(errno));
		 return -1;
	 }

	 fm_fd = -1;

	 printf("FM close success !\n");
	 return 0;

}

int fm_open(void)
{
	 int ret = 0;
	 int value = 0;
	 //int fm_fd =-1;
	 struct fm_tune_parm parm;
//	unsigned char  cmd_buf[30] ={0};
//	 memset(&parm, sizeof(struct fm_tune_parm));

// add "O_NONBLOCK" just in order to debug RDS by test tool


	 value = 1;
	 ret = ioctl(fm_fd, FM_IOCTL_POWERUP, &parm);
	 if (0 != ret) {
		 printf("FM enable failed!");
		 goto ENABLE_FAILE;
	 }
//        sprintf(cmd_buf, "autotest_fmtest=1");
//        SendAudioTestCmd((const unsigned char*)cmd_buf,sizeof(cmd_buf));

	 return 0;

 ENABLE_FAILE:
	 ret = close(fm_fd);
	 if (0 != ret) {
		 printf("FM close faile! errno[%d] = %s", errno, strerror(errno));
	 }

	 fm_fd = -1;

	 return -1;

}


 static int fm_close(void)
 {
	 int type;
	 int ret;
//	unsigned char  cmd_buf[30] ={0};

	 type = 0;
//	  sprintf(cmd_buf, "autotest_fmtest=0");
 //      SendAudioTestCmd((const unsigned char*)cmd_buf,sizeof(cmd_buf));

	 printf("fm_fd =%d,\n",fm_fd);
	 ret = ioctl(fm_fd, FM_IOCTL_POWERDOWN, &type);
	 if (0 != ret) {
		 printf("FM disable faile!\n");
		 return -1;
	 }

	 return 0;
 }

static int fm_tune(unsigned short set_freq)
{
	int ret;
	struct fm_tune_parm parm;
	parm.freq = set_freq;
	ret = ioctl(fm_fd, FM_IOCTL_TUNE, &parm);
	if (0 != ret) {
		printf("FM tune faile!\n");
		return -1;
	 }
	 printf("FM tune success !\n");

	 return 0;

}

static int fm_seekup(unsigned char direction)
{
	int ret;
	struct fm_seek_parm parm;
	unsigned short find_freq =0;
	parm.seekdir = direction;
	ret = ioctl(fm_fd, FM_IOCTL_SEEK, &parm);
	if(ret == 0) {
		find_freq = parm.freq;
		}
	printf("the up next freq ***%d*** is find\n",find_freq);
	return 0;

}


static int fm_seekdown(unsigned char direction)
{
	int ret;
	struct fm_seek_parm parm;
	unsigned short find_freq =0;
	parm.seekdir = direction;
	ret = ioctl(fm_fd, FM_IOCTL_SEEK, &parm);
	if(ret == 0) {
		find_freq = parm.freq;
		}
	printf("the down freq ***%d*** is find\n",find_freq);
	return 0;
}


static int fm_mute(int mute)
{
	int ret;
	int tmp = mute;
	ret = ioctl(fm_fd, FM_IOCTL_MUTE, &tmp);
	if (ret) {
		printf("fm mute failed!\n");
		}
	printf("FM mute success !\n");
	return 0;

}

static int fm_setvolume(unsigned char vol)
{
	int ret;
	int tmp = vol;
	ret = ioctl(fm_fd, FM_IOCTL_SETVOL, &tmp);
	if (ret) {
		printf("fm set volume failed!\n");
		}
	printf("FM set volume success !\n");
	return 0;
}

static int fm_getvolume(int *vol)
{
	int ret;
	unsigned char tmp = 0;
	ret = ioctl(fm_fd, FM_IOCTL_GETVOL, &tmp);
	*vol = (int)tmp;
	if (ret) {
		printf("fm set volume failed!\n");
		}
	printf("FM get volume = %d\n", tmp);
	return 0;
}

static int fm_rds_on(void)
{
	int ret =0;
	unsigned char rds_on =1;
	 ret = ioctl(fm_fd, FM_IOCTL_RDS_ONOFF, &rds_on);
	 if (0 != ret) {
		 printf("FM rds on faile!\n");
		 return -1;
	 }
	 printf("FM rds on success !\n");
	 return 0;
}

static int fm_rds_off(void)
{
	int ret =0;
	unsigned char rds_on =0;
	 ret = ioctl(fm_fd, FM_IOCTL_RDS_ONOFF, &rds_on);
	 if (0 != ret) {
		 printf("FM rds off faile!\n");
		 return -1;
	 }
	 printf("FM rds off success !\n");
	 return 0;
}

static int fm_getcurr_rssi(void)
{
	int ret =0;
	int rssi=0;
	 ret = ioctl(fm_fd, FM_IOCTL_GETRSSI, &rssi);
	 if (0 != ret) {
		 printf("FM get current RSSI fail !!!\n");
		 return -1;
	 }
	 printf("FM get current RSSI success !,the value==%d\n",rssi);
	 return 0;
}

static int fm_getcurr_snr(void)
{
	int ret =0;
	int snr=0;
	 ret = ioctl(fm_fd, FM_IOCTL_GETSNR, &snr);
	 if (0 != ret) {
		 printf("FM get SNR failed\n");
		 return -1;
	 }
	 printf("FM SNR = %d\n",snr);
	 return 0;
}

static int fm_scan_all(void)
{
	int ret =0;
	int i;
	struct fm_scan_all_parm parm;
	memset(&parm, 0x0, sizeof(struct fm_scan_all_parm));
	 ret = ioctl(fm_fd, FM_IOCTL_SCAN, &parm);
	 if (0 != ret) {
		 printf("FM scan all faile!\n");
		 return -1;
	 }
	 printf("FM scan chanel list is:");
	 for(i=0; i<parm.chanel_num;i++)
		printf("    %d",parm.freq[i]);
	 return 0;
}

static int fm_stop_scan(void)
{
	int ret =0;
	 ret = ioctl(fm_fd, FM_IOCTL_STOP_SCAN, NULL);
	 if (0 != ret) {
		 printf("FM stop scan faile!\n");
		 return -1;
	 }
	 printf("FM stop scan success !\n");
	 return 0;
}

static int fm_set_monostereo(void)
{
	int ret =0;
	unsigned char flag = 0;
	 ret = ioctl(fm_fd, FM_IOCTL_SETMONOSTERO, &flag);
	 if (0 != ret) {
		 printf("FM set mono stereo faile!\n");
		 return -1;
	 }
	 printf("FM set mono stereo success !\n");
	 return 0;
}

static int fm_read_write_reg(void)
{
	int ret =0;
	struct fm_ctl_parm parm;
	 ret = ioctl(fm_fd, FM_IOCTL_RW_REG, &parm);
	 if (0 != ret) {
		 printf("FM read write register faile!\n");
		 return -1;
	 }
	 printf("FM addr=0x%x, value =0x%x\n",parm.addr, parm.val);
	 return 0;
}

static int fm_get_pamd(void)
{
	int ret =0;
	unsigned char PAMD =0;
	 ret = ioctl(fm_fd, FM_IOCTL_GETCURPAMD, &PAMD);
	 if (0 != ret) {
		 printf("FM get pamd faile!\n");
		 return -1;
	 }
	 printf("FM PAMD = %d \n",PAMD);
	 return 0;
}

static int fm_get_rds_data(void)
{
	int ret =0;
	unsigned char ps[8] ={0};
	unsigned char rt[64] ={0};
	unsigned short event_status = 0;
	struct fm_rds_data rds;
	int size=0;
	size = read(fm_fd, &rds, sizeof(rds));
	event_status = rds.event_status;
	if(size == sizeof(rds))
		printf("RDS read succsessful\n");
	else
		printf("RDS read error\n");
	printf("event_status =0x%x\n", event_status);
	memcpy(ps, &rds.ps_data.PS[3][0], 8);
	memcpy(rt, &rds.rt_data.textdata[3][0], 64);
	printf("PS= %s\n",ps);
	printf("RT = %s\n",rt);
	 return 0;
}

static int fm_open_audio_path(void)
{
	char  cmd_buf[30] ={0};
	sprintf(cmd_buf, "autotest_fmtest=1");
	SendAudioTestCmd((const unsigned char*)cmd_buf,sizeof(cmd_buf));
	printf("open audio path successful!\n");
	return 0;
}

static int fm_play_audio(void)
{
	char  cmd_buf[30] ={0};
	sprintf(cmd_buf, "autotest_fmtest=2");
	SendAudioTestCmd((const unsigned char*)cmd_buf,sizeof(cmd_buf));
	printf("audio playing successful !\n");
	return 0;

}

static int fm_close_audio_path(void)
{
	char  cmd_buf[30] ={0};
	sprintf(cmd_buf, "autotest_fmtest=0");
	SendAudioTestCmd((const unsigned char*)cmd_buf,sizeof(cmd_buf));
	printf("close audio path successful!\n");
	return 0;
}


int main (int argc, char** argv)
{
        int fd, opt;
	 int input;
	 int freq;
	 int mute;
	 int volume;

	 // if you input fmtest -s -d, so:argc = 3, argv[0]=fmtest,argv[1]=-s
	printf("argc = %d, argv[0]=%s,argv[1]=%s\n",argc,argv[0],argv[1]);
	while(1){

	 printf("please input the action number,if you input other number,it will exit the process\n");
	 printf("0: open /dev/fm \n");
	 printf("1:  open fm\n");
	 printf("2:  close fm\n");
	 printf("3:  tune fm\n");
	 printf("4:  seek up fm\n");
	 printf("5:  seek down fm\n");
	 printf("6:  mute fm\n");
	 printf("7:  set volume fm\n");
	 printf("8:  get volume fm\n");
	 printf("9:  audio :open audio path\n");
	 printf("10:  audio: playing in  audio path\n");
	 printf("11:  audio : close audio path\n");
	 printf("12: RDS ON\n");
	 printf("13: RDS OFF\n");
	 printf("14: Get current RSSI\n");
	 printf("15 : Get current SNR\n");
	 printf("16 : Scan all chanel\n");
	 printf("17 : stop scan all\n");
	 printf("18 : Set Stereo Mono\n");
	 printf("19 : Read and write Register\n");
	 printf("20 : Get current PAMD\n");
	 printf("21 : read RDS data.... \n");
	 printf("22: close /dev/fm \n");

	 scanf("%d",&input);

	 if(input == 0) {
		fm_open_dev();
	}

	 else if(input ==1)
	 	{
	 	printf("**************************\n");
	 	printf("open fm\n");
	      fm_open();
		printf("**************************\n");
	 	}
	 else if(input ==2)
	 	{
	 	printf("**************************\n");
	 	printf("close fm\n");
		fm_close();
		printf("**************************\n");
	 	}

	 else if(input ==3){
	 	printf("please input the frequency. For example: 8750\n");
		scanf("%d",&freq);

		printf("**************************\n");
	 	printf("tune fm\n");
		fm_tune(freq);
		printf("**************************\n");

	 	}

	 else if (input == 4) {
	 	printf("**************************\n");
	 	fm_seekup(0);
		printf("**************************\n");
	 	}

	 else if (input ==5) {
	 	printf("**************************\n");
	 	fm_seekdown(1);
		printf("**************************\n");

	 	}

	 else if (input ==6) {
	 	printf("please input 0 or 1,(1:mute;0:unmute)\n");
		scanf("%d",&mute);
	 	printf("**************************\n");
		fm_mute(mute);
		printf("**************************\n");

	 	}

	 else if (input ==7) {
	 	printf("please input the volume,(0~255)\n");
		scanf("%d",&volume);
	 	printf("**************************\n");
		fm_setvolume(volume);
		printf("**************************\n");
		}

	 else if (input == 8) {
		printf("**************************\n");
		fm_getvolume(&volume);
		printf("**************************\n");
	 	}

	 else if (input ==9) {
		printf("**************************\n");
		fm_open_audio_path();
		printf("**************************\n");

		}

	 else if (input ==10) {
		printf("**************************\n");
		fm_play_audio();
		printf("**************************\n");

		}

	 else if (input ==11) {
		printf("**************************\n");
		fm_close_audio_path();
		printf("**************************\n");

		}

	 else if (input ==12) {
		printf("**************************\n");
		fm_rds_on();
		printf("**************************\n");

		}

	 else if (input ==13) {
		printf("**************************\n");
		fm_rds_off();
		printf("**************************\n");

		}

	 else if (input ==14) {
		printf("**************************\n");
		fm_getcurr_rssi();
		printf("**************************\n");
		}

	 else if (input ==15) {
		printf("**************************\n");
		fm_getcurr_snr();
		printf("**************************\n");
		}

	else if (input ==16) {
		printf("**************************\n");
		fm_scan_all();
		printf("**************************\n");
		}

	else if (input ==17) {
		printf("**************************\n");
		fm_stop_scan();
		printf("**************************\n");
		}

	else if (input ==18) {
		printf("**************************\n");
		fm_set_monostereo();
		printf("**************************\n");
		}

	else if (input ==19) {
		printf("**************************\n");
		fm_read_write_reg();
		printf("**************************\n");
		}

	else if (input ==20) {
		printf("**************************\n");
		fm_get_pamd();
		printf("**************************\n");
		}

	else if (input ==21) {
		printf("**************************\n");
		fm_get_rds_data();
		printf("**************************\n");
		}
	else if (input ==22) {
		printf("**************************\n");
		fm_close_dev();
		printf("**************************\n");
		}


	 else
	 	return 0;
	}

        return 0;
}

