#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>
#include <player.h>
#include <playerstate.h>
#include <xls_shop.h>

#define AP_SETTINGS_LOCATIONS_BITFIELD_SIZE 0x30
#define AP_SETTINGS_INIT_MAGICVALUE 0x45424245 // 'EBBE' in ASCII :)

typedef struct APSettings {
    u8 location_bitfield[AP_SETTINGS_LOCATIONS_BITFIELD_SIZE];
    BreathType starting_breath;
    u32 starting_abilities;
    bool free_realm_travel_enable;
    bool skip_realm_intro_cutscenes;
    bool skip_cutscene_button;
    bool allow_teleport_to_hub;
    u32 init;

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
    xlsShoppingItem xls_shop_items[100];
} APSettings;

extern APSettings g_gamestate_ap_settings;

#define AP_GAMESTATE_SHOP_SPREADSHEET_START ((void*)(&g_gamestate_ap_settings.xls_shop_sheetcount_ALWAYS_1))

#endif /* AP_SETTINGS_H */