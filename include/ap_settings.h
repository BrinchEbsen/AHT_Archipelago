#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>
#include <player.h>

typedef struct APSettings {
    u8 location_bitfield[0x30];
    BreathType starting_breath;
    bool firebreath_enable;
    bool glide_enable;
    bool charge_enable;
    bool swim_enable;
    bool free_realm_travel_enable;
} APSettings;

extern APSettings g_gamestate_ap_settings;

#endif /* AP_SETTINGS_H */