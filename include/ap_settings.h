#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>

#define LOCATION_BITFIELD_SIZE 0x30
extern u8 g_location_bitfield[];

extern bool g_ap_enable_archipelago;
extern bool g_ap_firebreath_enable;
extern bool g_ap_breaths_as_locations;
extern bool g_ap_enable_free_realm_travel;

#endif /* AP_SETTINGS_H */