#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>
#include <player.h>
#include <playerstate.h>
#include <xls_shop.h>

#define AP_SETTINGS_LOCATIONS_BITFIELD_SIZE 0x30
#define AP_SETTINGS_INIT_MAGICVALUE 0x45424245 // 'EBBE' in ASCII :)

#define SHOP_NUM_VANILLA_ENTRIES 15
#define SHOP_TOTAL_NUM_ENTRIES 100
#define AP_TEXT_ENTRY_HASHCODE_BASE 0x28010000

typedef struct APSettings_TextEntry
{
    char text[50];
} APSettings_TextEntry;

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
    xlsShoppingItem xls_shop_items[SHOP_TOTAL_NUM_ENTRIES];

    APSettings_TextEntry shop_text[SHOP_TOTAL_NUM_ENTRIES - SHOP_NUM_VANILLA_ENTRIES];
} APSettings;

extern APSettings g_gamestate_ap_settings;

#define AP_GAMESTATE_SHOP_SPREADSHEET_START ((void*)(&g_gamestate_ap_settings.xls_shop_sheetcount_ALWAYS_1))

#endif /* AP_SETTINGS_H */