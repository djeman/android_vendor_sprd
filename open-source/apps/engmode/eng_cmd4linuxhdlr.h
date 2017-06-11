
#ifndef __ENG_CMD4LINUXHDLR_H__
#define __ENG_CMD4LINUXHDLR_H__

#define SPRDENG_OK			"OK"
#define SPRDENG_ERROR		"ERROR"
#define ENG_STREND			"\r\n"
#define ENG_TESTMODE		"engtestmode"
#define ENG_BATVOL			"/sys/class/power_supply/battery/real_time_voltage"
#define ENG_STOPCHG			"/sys/class/power_supply/battery/stop_charge"
#define ENG_CURRENT			"/sys/class/power_supply/battery/real_time_current"
#define ENG_BATTVOL_AVG 	"/sys/class/power_supply/battery/current_avg"
#define ENG_BATTVOL_NOW 	"/sys/class/power_supply/battery/voltage_now"
#define ENG_BATTCHG_STS 	"/sys/class/power_supply/battery/status"
#define ENG_BATTTEMP   		"/sys/class/power_supply/battery/temp"
#define ENG_BATTTEMP_ADC 	"/sys/class/power_supply/battery/temp_adc"
#define ENG_BATTCAPACITY 	"/sys/class/power_supply/battery/capacity"
#define ENG_WPATEMP         "/sys/devices/platform/sprd_temprf/temprf_wpa_temp"
#define ENG_WPATEMP_ADC     "/sys/devices/platform/sprd_temprf/temprf_wpa_temp_adc"
#define ENG_DCXOTEMP		"/sys/devices/platform/sprd_temprf/temprf_dcxo_temp"
#define ENG_DCXOTEMP_ADC    "/sys/devices/platform/sprd_temprf/temprf_dcxo_temp_adc"
#define ENG_RECOVERYCMD		"/cache/recovery/command"
#define ENG_RECOVERYDIR		"/cache/recovery"
#define ENG_CHARGERTEST_FILE "/productinfo/chargertest.file"
#define IQMODE_FLAG_PATH        "/productinfo/iqmode"

#define CMD_CALI 	7

typedef enum{
    CMD_SENDKEY = 0,	// 0
    CMD_GETICH,		// 1
    CMD_ETSRESET, 	// 2
    CMD_RPOWERON, 	// 3
    CMD_GETVBAT, 	// 4
    CMD_STOPCHG,	// 5
    CMD_TESTMMI, 	// 6
    CMD_BTTESTMODE,	// 7
    CMD_GETBTADDR, 	// 8
    CMD_SETBTADDR,	// 9
    CMD_GSNR, 		// 10
    CMD_GSNW,		// 11
    CMD_GETWIFIADDR, 	// 12
    CMD_SETWIFIADDR,	// 13
    CMD_CGSNW, 		// 14
    CMD_ETSCHECKRESET, 	// 15
    CMD_SIMCHK, 	// 16
    CMD_ATDIAG,		// 17
    CMD_INFACTORYMODE, 	// 18
    CMD_FASTDEEPSLEEP,	// 19
    CMD_CHARGERTEST, 	// 20
    CMD_SPBTTEST,	// 21
    CMD_SPWIFITEST,	// 22
    CMD_SPGPSTEST, 	// 23
    CMD_SPWIQ, 		// 24
    CMD_E0,		// 25
    CMD_E1,		// 26
    CMD_HEADINFO, 	// 27
    CMD_MITSRFTS,	// 28
    CMD_RTCTEST,	// 29
    CMD_CPRMTEST, 	// 30
    CMD_DEVCONINFO,	// 31
    CMD_BATGETLEVEL, 	// 32
    CMD_VERSNAME,	// 33
    CMD_FCBTTEST, 	// 34
    CMD_FCFMTEST,	// 35
    CMD_FCMPTEST, 	// 36
    CMD_IMEMTEST,	// 37
    CMD_EMEMTEST, 	// 38
    CMD_GEOMAGSS,	// 39
    CMD_SPKSTEST, 	// 40
    CMD_PROXIMIT,	// 41
    CMD_GPSSTEST, 	// 42
    CMD_HDMITEST, 	// 43
    CMD_NFCMTEST, 	// 44
    CMD_FSBUILDC, 	// 45
    CMD_FACTOLOG, 	// 46
    CMD_ACSENSOR, 	// 47
    CMD_CAMETEST, 	// 48
    CMD_VIBRTEST, 	// 49
    CMD_BATTTEST, 	// 50
    CMD_FCEPTEST,	// 51
    CMD_FCESTEST,	// 52
    CMD_WIFITEST, 	// 53
    CMD_GYROSCOP,	// 54
    CMD_AROTATEC,	// 55
    CMD_FUNCTEST,	// 56
    CMD_SETTESTNV,	// 57
    CMD_GETTESTNV,	// 58
    CMD_SETFULLTESTNV,	// 59
    CMD_GETFULLTESTNV,	// 60
    CMD_SETFULLHISTNV,	// 61
    CMD_LOGERASE,	// 62
    CMD_SETFDATA,	// 63
    CMD_SETFULLFDATA,	// 64
    CMD_GETFDATA,	// 65
    CMD_GETFULLFDATA,	// 66
    CMD_HWINDICK,	// 67
    CMD_SERIALNO,	// 68
    CMD_FAILDUMP,	// 69
    CMD_KEYHOLD,	// 70
    CMD_BATTCALI,	// 71
    CMD_PRECONFG,	// 72
    CMD_BTIDTEST,	// 73
    CMD_WIFIIDRV,	// 74
    CMD_HDCPTEST,	// 75
    CMD_KSTRINGB,	// 76
    CMD_MEMOSIZE,	// 77
    CMD_DISPSIZE,	// 78
    CMD_PORTCHAN,	// 79
    CMD_MSLSECUR,	// 80
    CMD_AKSEEDNO,	// 81
    CMD_IMEITEST,	// 82
    CMD_PRODCODE,	// 83
    CMD_CALIDATE,	// 84
    CMD_LVOFLOCK,	// 85
    CMD_CONTROLN,	// 86
    CMD_DETALOCK,	// 87
    CMD_FUELGAIC,	// 88
    CMD_FACTORSD,	// 89
    CMD_RSTVERIF,	// 90
    CMD_LOCKREAD,	// 91
    CMD_TOUCHKEY,	// 92
    CMD_TSPPTEST,	// 93
    CMD_DEBUGLVC,	// 94
    CMD_IMEICERT,	// 95
    CMD_IMEISIGN,	// 96
    CMD_WPROTECT,	// 97
    CMD_SECUREOS,	// 98
    CMD_SYSSCOPE,	// 99
    CMD_KEY,		// 100
    CMD_TOUCH,		// 101
    CMD_MICSD,		// 102
    CMD_TEMPTEST,	// 103
    CMD_INITTEST,	// 104
    CMD_CALLCONN,	// 105
    CMD_FAILHIST,	// 106
    CMD_LOOPTEST,	// 107
    CMD_MULFUNCF,	// 108
    CMD_SVCIFPGM,	// 109
    CMD_WHO,		// 110
    CMD_NFCTESTSCRIP,	// 111
    CMD_SIMSTATE,	// 112
    CMD_GETCTSIM,	// 113
    CMD_LAUNCHPKG,	// 114
    CMD_GETCOUNTIMAGE, 	// 115
    CMD_GETCOUNTVIDEO,	// 116
    CMD_GETEMERGENCYRESULT, // 117
    CMD_RAMSIZEC,	// 118
    CMD_SCMMONIT,	// 119
    CMD_SWDLMODE,	// 120
    CMD_CBLKFTDF,	// 121
    CMD_FIRMVERS,	// 122
    CMD_POWRESET,	// 123
    CMD_SIMDETECT,	// 124
    CMD_ISDBTEST,	// 125
    CMD_CORECTRL,	// 126
    CMD_OTGGTEST,	// 127
    CMD_GRIPSENS,	// 128
    CMD_BACKUPCHK,	// 129
    CMD_REACTIVE,	// 130

    CMD_END
}ENG_CMD;


typedef enum{
    CMD_INVALID_TYPE,
    CMD_TO_AP, /* handled by AP */
    CMD_TO_APCP /* handled by AP and CP */
}eng_cmd_type;

struct eng_linuxcmd_str{
    int index;
    eng_cmd_type type;
    char *name;
    int (*cmd_hdlr)(char *, char *);
};

void eng_set_linuxcmd(int califlag);
int eng_at2linux(char *buf);
int eng_linuxcmd_hdlr(int cmd, char *req, char* rsp);
eng_cmd_type eng_cmd_get_type(int cmd);

#endif
