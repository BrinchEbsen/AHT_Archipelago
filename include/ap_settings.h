#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>
#include <player.h>

#define AP_SETTINGS_LOCATIONS_BITFIELD_SIZE 0x30
#define AP_SETTINGS_INIT_MAGICVALUE 0x45424245

typedef struct APSettings {
    u8 location_bitfield[AP_SETTINGS_LOCATIONS_BITFIELD_SIZE];
    BreathType starting_breath;
    bool firebreath_enable;
    bool glide_enable;
    bool charge_enable;
    bool swim_enable;
    bool free_realm_travel_enable;
    bool skip_realm_intro_cutscenes;
    u32 init;
} APSettings;

extern APSettings g_gamestate_ap_settings;

#endif /* AP_SETTINGS_H */