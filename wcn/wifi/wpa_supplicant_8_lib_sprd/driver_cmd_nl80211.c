/*
 * Driver interaction with extended Linux CFG8021
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 */

#include <net/if.h>

#include "includes.h"
#include "common.h"
#include "linux_ioctl.h"
#include "driver_nl80211.h"
#include "wpa_supplicant_i.h"
#include "android_drv.h"

typedef struct android_wifi_priv_cmd {
       char *buf;                //pointer to struct driver_cmd_msg
       int used_len;             //length of driver_cmd_msg including data
       int total_len;
} android_wifi_priv_cmd;

struct driver_cmd_msg
{
	uint16_t  msg_type;    //CMD_SUBTYPE_XX
	uint16_t msg_len;      //msg_data length
	char msg_data[];
};

#define CMD_SUBTYPE_MAX_NUM_STA (4)
#define CMD_SUBTYPE_MIRACAST_MODE (5)

static int drv_errors = 0;

static void wpa_driver_send_hang_msg(struct wpa_driver_nl80211_data *drv)
{
       drv_errors++;
       if (drv_errors > DRV_NUMBER_SEQUENTIAL_ERRORS) {
               drv_errors = 0;
               wpa_msg(drv->ctx, MSG_INFO, WPA_EVENT_DRIVER_STATE "HANGED");
       }
}

int wpa_driver_nl80211_driver_cmd(void *priv, char *cmd, char *buf,
				  size_t buf_len )
{
	struct i802_bss *bss = priv;
	struct wpa_driver_nl80211_data *drv = bss->drv;
	struct ifreq ifr;
	android_wifi_priv_cmd priv_cmd;
	int ret = 0;

	wpa_printf(MSG_DEBUG, "%s: Driver cmd: %s\n", __func__, cmd);
	memset(&ifr, 0, sizeof(ifr));
	memset(&priv_cmd, 0, sizeof(priv_cmd));

	if (strcasecmp(cmd, "STOP") == 0) {
		linux_set_iface_flags(drv->global->ioctl_sock, bss->ifname, 0);
		wpa_msg(drv->ctx, MSG_INFO, WPA_EVENT_DRIVER_STATE "STOPPED");
	} else if (strcasecmp(cmd, "START") == 0) {
		linux_set_iface_flags(drv->global->ioctl_sock, bss->ifname, 1);
		wpa_msg(drv->ctx, MSG_INFO, WPA_EVENT_DRIVER_STATE "STARTED");
	} else if (strcasecmp(cmd, "MACADDR") == 0) {
		u8 macaddr[ETH_ALEN] = {};
		ret = linux_get_ifhwaddr(drv->global->ioctl_sock, bss->ifname, macaddr);
		if (!ret) ret = snprintf(buf, buf_len, "Macaddr = " MACSTR "\n", MAC2STR(macaddr));
	} else if(strncasecmp(cmd, "MAX_STA", 7) == 0) {
		int hdrlen = 2*sizeof(unsigned short);
		char max_sta_num = *buf;
		wpa_printf(MSG_INFO, "max_sta_num: %d, buf_len: %d.", max_sta_num, buf_len);
		memset(buf, 0, buf_len);
		*(unsigned short *)buf = CMD_SUBTYPE_MAX_NUM_STA;
		*(unsigned short *)(buf + hdrlen/2)= sizeof(max_sta_num);
		*(buf + hdrlen) = max_sta_num;
		buf_len = hdrlen + sizeof(max_sta_num);

               memset(&ifr, 0, sizeof(ifr));
               memset(&priv_cmd, 0, sizeof(priv_cmd));
               strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);
	       wpa_printf(MSG_DEBUG, "buf_len:%d.", buf_len);
               priv_cmd.buf = buf;
               priv_cmd.used_len = buf_len;
               priv_cmd.total_len = buf_len;
               ifr.ifr_data = &priv_cmd;

               if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 2, &ifr)) < 0) {
                       wpa_printf(MSG_ERROR, "%s: failed to issue private commands\n", __func__);
                       //wpa_driver_send_hang_msg(drv);
               } else {
                       drv_errors = 0;
                       wpa_printf(MSG_INFO, "%s %s len = %d, %d", __func__, buf, ret, strlen(buf));
               }

	}  else if (strncasecmp(cmd, "MIRACAST", 8) == 0) {
		struct driver_cmd_msg *miracast;
		int value = atoi(cmd+8);

		memset(buf, 0, buf_len);
		miracast = (struct driver_cmd_msg *)buf;
		miracast->msg_type = CMD_SUBTYPE_MIRACAST_MODE;
		miracast->msg_len = sizeof(int);
		memcpy(miracast->msg_data, &value, sizeof(value));

		priv_cmd.buf = (char *)miracast;
		priv_cmd.used_len = sizeof(*miracast) + miracast->msg_len;
		priv_cmd.total_len = priv_cmd.used_len;

		strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);
		ifr.ifr_data = &priv_cmd;

		if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 2, &ifr)) < 0) {
			wpa_printf(MSG_ERROR, "%s: failed to issue private commands(%s), total_len=%d, value=%d\n",
				__func__, strerror(errno), priv_cmd.total_len, value);
			//wpa_driver_send_hang_msg(drv);
		} else {
			drv_errors = 0;
		}

		memset(buf, 0, buf_len);
	} else if (strncasecmp(cmd, "SETSUSPENDMODE", 14) == 0) {
		memcpy(buf, cmd, strlen(cmd) + 1);
		memset(&ifr, 0, sizeof(ifr));
		memset(&priv_cmd, 0, sizeof(priv_cmd));
		strncpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);
		ifr.ifr_name[IFNAMSIZ - 1] = '\0';

		priv_cmd.buf = buf;
		priv_cmd.used_len = buf_len;
		priv_cmd.total_len = buf_len;
		ifr.ifr_data = &priv_cmd;

		if ((ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 4, &ifr)) < 0) {
			wpa_printf(MSG_ERROR, "%s: failed to issue private commands(%s)\n", __func__, strerror(errno));
			//wpa_driver_send_hang_msg(drv);
		} else {
			drv_errors = 0;
			ret = 0;
		}
	}
	return ret;
}

int wpa_driver_set_p2p_noa(void *priv, u8 count, int start, int duration)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	return 0;
}

int wpa_driver_get_p2p_noa(void *priv, u8 *buf, size_t len)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	/* Return 0 till we handle p2p_presence request completely in the driver */
	return 0;
}

int wpa_driver_set_p2p_ps(void *priv, int legacy_ps, int opp_ps, int ctwindow)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	return 0;
}

int wpa_driver_set_ap_wps_p2p_ie(void *priv, const struct wpabuf *beacon,
				 const struct wpabuf *proberesp,
				 const struct wpabuf *assocresp)
{
	wpa_printf(MSG_DEBUG, "%s: NOT IMPLETE", __func__);

	return 0;
}
