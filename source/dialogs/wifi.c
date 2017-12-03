/*
 * wifi.c
 *
 *  Created on: Nov 23, 2017
 *      Author: james
 */

#define G_LOG_DOMAIN	"Dialogs.Wifi"

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_atom.h>

#include <glib.h>

#include "rofi.h"
#include "dialogs/wifi.h"

#include "NetworkManager.h"

static NMDeviceWifi * wifi_device;

typedef struct
{
	unsigned int access_point_list_length;
	NMAccessPoint ** access_point_list;
	NMActiveConnection * activing_connection;
	char ** access_point_ssid_list;
} WifiModePrivateData;

static NMDeviceWifi * get_wifi_device (NMClient * client)
{
	NMDeviceWifi * wifi_device_tmp = NULL;

	void device_array_iteration_callback (gpointer device, gpointer user_data)
	{
		if (nm_device_get_device_type (device) == NM_DEVICE_TYPE_WIFI)
		{
			(* (NMDeviceWifi **) user_data) = (NMDeviceWifi *) device;
		}
	}

	if (client)
	{
		const GPtrArray * device_array = nm_client_get_all_devices (client);

		g_ptr_array_foreach(device_array, device_array_iteration_callback, &wifi_device_tmp);
	}

	return wifi_device_tmp;
}

static GPtrArray * get_access_points (NMDeviceWifi * wifi_device_tmp)
{
	GPtrArray * access_point_array = NULL;

	if (wifi_device_tmp)
	{
		access_point_array = nm_device_wifi_get_access_points (wifi_device_tmp);
	}

	return access_point_array;
}

static void update_wifi_mode_private_data (GPtrArray * access_point_array, WifiModePrivateData * private_data)
{
	void access_point_array_iteration_callback (gpointer access_point, gpointer user_data)
	{
		int index = private_data->access_point_list_length++;
		private_data->access_point_list[index] = (NMAccessPoint *) access_point;
		private_data->access_point_ssid_list[index] = ((GByteArray *) nm_access_point_get_ssid ((NMAccessPoint *) access_point))->data;
	}

	if (access_point_array)
	{
		// g_print ("Length: %d\n", access_point_array->len);
		private_data->access_point_list = (NMAccessPoint **) g_malloc_n (access_point_array->len, sizeof (NMAccessPoint *));
		private_data->access_point_ssid_list = (char **) g_malloc_n (access_point_array->len, sizeof (char *));
		private_data->access_point_list_length = 0;

		g_ptr_array_foreach (access_point_array, access_point_array_iteration_callback, private_data);
	}
}

static void wifi_device_scan (NMDeviceWifi * wifi_device_tmp)
{
	if (wifi_device_tmp)
	{
		nm_device_wifi_request_scan (wifi_device_tmp, NULL, NULL);
	}
}

static int wifi_mode_init( Mode * sw )
{
	NMClient * client = nm_client_new (NULL, NULL);

	if ( mode_get_private_data ( sw )  == NULL )
	{
		WifiModePrivateData * pd = g_malloc0( sizeof( *pd ) );
		mode_set_private_data( sw, (void *) pd );

		pd->activing_connection = nm_client_get_activating_connection (client);
		pd->access_point_list_length = 0;

		wifi_device = get_wifi_device (client);
		wifi_device_scan (wifi_device);

		GPtrArray * access_point_array = get_access_points (wifi_device);
		update_wifi_mode_private_data (access_point_array, pd);

	}

	return TRUE;
}

static int wifi_mode_get_num_entries ( const Mode *sw )
{
	const WifiModePrivateData *rmpd = (const WifiModePrivateData *) mode_get_private_data (sw);
	return rmpd->access_point_list_length;
}

static ModeMode wifi_mode_result ( Mode *sw, int mretv, char **input, unsigned int selected_line )
{
    ModeMode retv  = MODE_EXIT;

    return retv;
}

static void wifi_mode_destroy ( Mode *sw )
{
    WifiModePrivateData *rmpd = (WifiModePrivateData *) mode_get_private_data ( sw );
    if (rmpd != NULL) {
    	g_free (rmpd->access_point_list);
        g_free (rmpd);
        mode_set_private_data (sw, NULL);
    }
}

static int wifi_token_match ( const Mode *sw, rofi_int_matcher **tokens, unsigned int index )
{
    WifiModePrivateData *rmpd = (WifiModePrivateData *) mode_get_private_data ( sw );
    return helper_token_match ( tokens, rmpd->access_point_ssid_list[index] );
}

static char * wifi_mode_get_display_value ( const Mode *sw, unsigned int selected_line, G_GNUC_UNUSED int *state, G_GNUC_UNUSED GList **attr_list, int get_entry )
{
    WifiModePrivateData *rmpd = (WifiModePrivateData *) mode_get_private_data ( sw );

    char * ssid_string = (NMAccessPoint *) rmpd->access_point_ssid_list[selected_line];

    return get_entry ? g_strdup (ssid_string) : NULL;
}

#include "mode-private.h"

Mode wifi_mode =
{
	.name               = "wifi",
	.cfg_name_key       = "display-wifi",
	._init              = wifi_mode_init,
	._get_num_entries   = wifi_mode_get_num_entries,
	._result            = wifi_mode_result,
	._destroy           = wifi_mode_destroy,
	._token_match       = wifi_token_match,
	._get_display_value = wifi_mode_get_display_value,
	._get_completion    = NULL,
	._preprocess_input  = NULL,
	.private_data       = NULL,
	.free               = NULL
};
