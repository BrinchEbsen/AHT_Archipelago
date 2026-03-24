#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>
#include <player.h>
#include <playerstate.h>
#include <xls_shop.h>

#define AP_SETTINGS_LOCATIONS_BITFIELD_SIZE 0x30
#define AP_SETTINGS_KEYRINGS_BITFIELD_SIZE 0x2
#define AP_SETTINGS_INIT_MAGICVALUE 0x45424245 // 'EBBE' in ASCII :)

#define SHOP_NUM_VANILLA_ENTRIES 1
#define SHOP_TOTAL_NUM_ENTRIES 80
#define AP_TEXT_ENTRY_HASHCODE_BASE 0x28010000

#define AP_DEATHLINK_MODE_NONE      0
#define AP_DEATHLINK_MODE_SHIELDED  1
#define AP_DEATHLINK_MODE_FULL      2

typedef struct APSettings_TextEntry
{
    /* 0x0 */ bool been_bought;
    /* 0x1 */ u8 padding;
    /* 0x2 */ char text[48];
} APSettings_TextEntry; // Size: 0x32

typedef struct APSettings {
    u8 location_bitfield[AP_SETTINGS_LOCATIONS_BITFIELD_SIZE];
    u8 keyring_bitfield[AP_SETTINGS_KEYRINGS_BITFIELD_SIZE];
    u8 num_gem_packs_received;
    u8 num_lock_picks_received;
    u8 num_fire_ammo_received;
    u8 num_electric_ammo_received;
    u8 num_water_ammo_received;
    u8 num_ice_ammo_received;
    u8 deathlink_ingoing;
    bool deathlink_outgoing;
    bool infinite_butterfly_jar;
    bool randomize_shop;
    bool use_key_rings;

    bool skip_cutscene_button;
    bool allow_teleport_to_hub;
    bool allow_immediate_realm_access;
    bool disable_popups;
    bool instant_elevators;

    bool patch_been_written_to;
    u32 mw_seed;

    // For detecting whether the gamestate should initialize.
    // Always the ASCII value "EBBE" when initialized.
    u32 init;

    u8 boss_costs[4];
    u8 lg_door_costs[4];

    // Number of datasheets in this spreadsheet.
    // GUI_Shop only has 1 datasheet.
    int xls_shop_sheetcount_ALWAYS_1;

    // Offset from here until the datasheet.
    // This will always be 4 bytes.
    int xls_shop_sheet_offset_ALWAYS_4;

    // Number of rows in the datasheet.
    // This is the number of items in the shop (15 in vanilla).
    int xls_shop_rowcount;

    // The entries in the datasheet, each representing a shop item.
    xlsShoppingItem xls_shop_items[SHOP_TOTAL_NUM_ENTRIES];

    APSettings_TextEntry shop_text[SHOP_TOTAL_NUM_ENTRIES - SHOP_NUM_VANILLA_ENTRIES];
} APSettings;

extern APSettings g_gamestate_ap_settings;

#define AP_GAMESTATE_SHOP_SPREADSHEET_START ((void*)(&g_gamestate_ap_settings.xls_shop_sheetcount_ALWAYS_1))
#define AP_GAMESTATE_SHOP_IS_RANDOMIZED (g_gamestate_ap_settings.randomize_shop)
#define AP_GAMESTATE_USE_KEY_RINGS (g_gamestate_ap_settings.use_key_rings)

#endif /* AP_SETTINGS_H */