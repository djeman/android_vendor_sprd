#ifndef __FMTEST_H__
#define __FMTEST_H__

struct fm_tune_parm {
    unsigned char err;
    unsigned char band;
    unsigned char space;
    unsigned char hilo;
    unsigned short freq;
};

struct fm_seek_parm {
	unsigned char err;
	unsigned char band;
	unsigned char space;
	unsigned char hilo;
	unsigned char seekdir;
	unsigned char seekth;
	unsigned short freq;
};

struct fm_scan_all_parm {
unsigned char band;//87.5~108,76~
unsigned char space;//50 or 100KHz
unsigned char chanel_num;
unsigned short freq[36]; // OUT parameter
};

struct fm_ctl_parm {
    unsigned char err;
    unsigned char addr;
    unsigned short val;
    unsigned short rw_flag; // 0:write, 1:read
};

struct rdslag {
	uint8_t TP;
	uint8_t TA;
	uint8_t music;
	uint8_t stereo;
	uint8_t artificial_head;
	uint8_t compressed;
	uint8_t dynamic_pty;
	uint8_t text_ab;
	uint32_t flag_status;
};

struct ct_info {
	uint16_t month;
	uint16_t day;
	uint16_t year;
	uint16_t hour;
	uint16_t minute;
	uint8_t local_time_offset_signbit;
	uint8_t local_time_offset_half_hour;
};

struct  af_info {
	int16_t AF_NUM;
	int16_t AF[2][25];
	uint8_t addr_cnt;
	uint8_t ismethod_a;
	uint8_t isafnum_get;
};

struct  ps_info {
	uint8_t PS[4][8];
	uint8_t addr_cnt;
};

struct  rt_info {
	uint8_t textdata[4][64];
	uint8_t getlength;
	uint8_t isrtdisplay;
	uint8_t textlength;
	uint8_t istypea;
	uint8_t bufcnt;
	uint16_t addr_cnt;
};

struct rds_group_cnt {
	unsigned long total;
	unsigned long groupA[16]; /* RDS groupA counter*/
	unsigned long groupB[16]; /* RDS groupB counter */
};

enum rds_group_cnt_opcode {
	RDS_GROUP_CNT_READ = 0,
	RDS_GROUP_CNT_WRITE,
	RDS_GROUP_CNT_RESET,
	RDS_GROUP_CNT_MAX
};

struct rds_group_cnt_req {
	int err;
	enum rds_group_cnt_opcode op;
	struct rds_group_cnt gc;
};

struct fm_rds_data {
	struct ct_info CT;
	struct rdslag RDSFLAG;
	uint16_t PI;
	uint8_t switch_tp;
	uint8_t PTY;
	struct  af_info af_data;
	struct  af_info afon_data;
	uint8_t radio_page_code;
	uint16_t program_item_number_code;
	uint8_t extend_country_code;
	uint16_t language_code;
	struct  ps_info ps_data;
	uint8_t ps_on[8];
	struct  rt_info rt_data;
	uint16_t event_status;
	struct rds_group_cnt gc;
};


#define FM_IOC_MAGIC        0xf5
#define FM_IOCTL_POWERUP       _IOWR(FM_IOC_MAGIC, 0, struct fm_tune_parm*)
#define FM_IOCTL_POWERDOWN     _IOWR(FM_IOC_MAGIC, 1, int *)
#define FM_IOCTL_TUNE          _IOWR(FM_IOC_MAGIC, 2, struct fm_tune_parm*)
#define FM_IOCTL_SEEK          _IOWR(FM_IOC_MAGIC, 3, struct fm_seek_parm*)
#define FM_IOCTL_SETVOL        _IOWR(FM_IOC_MAGIC, 4, unsigned int*)
#define FM_IOCTL_GETVOL        _IOWR(FM_IOC_MAGIC, 5, unsigned int*)
#define FM_IOCTL_MUTE          _IOWR(FM_IOC_MAGIC, 6, unsigned int*)
#define FM_IOCTL_GETRSSI       _IOWR(FM_IOC_MAGIC, 7, int*)
#define FM_IOCTL_GETSNR       _IOWR(FM_IOC_MAGIC, 71, int*)
#define FM_IOCTL_SCAN          _IOWR(FM_IOC_MAGIC, 8, struct fm_scan_all_parm*)
#define FM_IOCTL_STOP_SCAN     _IO(FM_IOC_MAGIC,   9)
#define FM_IOCTL_RW_REG        _IOWR(FM_IOC_MAGIC, 12, struct fm_ctl_parm*)
#define FM_IOCTL_GETCURPAMD    _IOWR(FM_IOC_MAGIC, 14, unsigned char*)
#define FM_IOCTL_RDS_ONOFF     _IOWR(FM_IOC_MAGIC, 18, unsigned char*)
#define FM_IOCTL_SETMONOSTERO _IOWR(FM_IOC_MAGIC, 37, unsigned char*)



#endif
