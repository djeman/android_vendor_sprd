
#include <sys/types.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "FMLIB_CUST"

#ifdef __cplusplus
extern "C" {
#endif

struct fm_fake_channel
{
    int freq;
    int rssi_th;
    int reserve;
};

struct fm_fake_channel_t
{
    int size;
    struct fm_fake_channel *chan;
};

struct CUST_cfg_ds
{
    int16_t chip;
    int32_t band;
    int32_t low_band;
    int32_t high_band;
    int32_t seek_space;
    int32_t max_scan_num;
    int32_t seek_lev;
    int32_t scan_sort;
    int32_t short_ana_sup;
    int32_t rssi_th_l2;
    struct fm_fake_channel_t *fake_chan;
};

// band
#define FM_BAND_UNKNOWN 0
#define FM_BAND_UE      1 // US/Europe band  87.5MHz ~ 108MHz (DEFAULT)
#define FM_BAND_JAPAN   2 // Japan band      76MHz   ~ 90MHz
#define FM_BAND_JAPANW  3 // Japan wideband  76MHZ   ~ 108MHz
#define FM_BAND_SPECIAL 4 // special   band  between 76MHZ   and  108MHz
#define FM_BAND_DEFAULT FM_BAND_UE

// freq min max
#define FM_UE_FREQ_MIN      875
#define FM_UE_FREQ_MAX      1080
#define FM_JP_FREQ_MIN      760
#define FM_JP_FREQ_MAX      900
#define FM_JPW_FREQ_MIN     760
#define FM_JPW_FREQ_MAX     1080
#define FM_FREQ_MIN_DEFAULT FM_UE_FREQ_MIN
#define FM_FREQ_MAX_DEFAULT FM_UE_FREQ_MAX

#define FM_SEEK_SPACE 1

#define FMR_SCAN_CH_SIZE    40
#define FM_MAX_CHL_SIZE FMR_SCAN_CH_SIZE

#define FM_SEEKTH_LEVEL_DEFAULT 4

//scan sort algorithm 
enum{
    FM_SCAN_SORT_NON = 0,
    FM_SCAN_SORT_UP,
    FM_SCAN_SORT_DOWN,
    FM_SCAN_SORT_MAX
};

#define FM_SCAN_SORT_SELECT FM_SCAN_SORT_NON

#define FM_CHIP_DESE_RSSI_TH (-102)

#define FM_CHIP_MARLIN 0x2341

#define MARLIN_FM_FAKE_CHANNEL 	{ }

static struct fm_fake_channel fake_ch[] = MARLIN_FM_FAKE_CHANNEL;

static struct fm_fake_channel_t fake_ch_info = {0, 0};

int CUST_get_cfg(struct CUST_cfg_ds *cfg)
{
	cfg->chip = FM_CHIP_MARLIN;
	cfg->band = FM_BAND_DEFAULT; // 1, UE; 2, JAPAN; 3, JAPANW
	cfg->low_band = FM_FREQ_MIN_DEFAULT;
	cfg->high_band = FM_FREQ_MAX_DEFAULT;
	cfg->seek_space = FM_SEEK_SPACE;	//FM radio seek space,5:50KHZ; 1:100KHZ; 2:200KHZ

	cfg->max_scan_num = FM_MAX_CHL_SIZE;
	cfg->seek_lev = FM_SEEKTH_LEVEL_DEFAULT;
	
	cfg->scan_sort = FM_SCAN_SORT_SELECT;

	cfg->short_ana_sup = false;

	cfg->rssi_th_l2 = FM_CHIP_DESE_RSSI_TH;
    
	fake_ch_info.chan = fake_ch;
	fake_ch_info.size = sizeof(fake_ch)/sizeof(fake_ch[0]);
	cfg->fake_chan = &fake_ch_info;
	return 0;
}

#ifdef __cplusplus
}
#endif

