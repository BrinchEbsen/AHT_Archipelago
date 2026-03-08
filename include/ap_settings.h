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
    /* 0x0  */ u8 location_bitfield[AP_SETTINGS_LOCATIONS_BITFIELD_SIZE];
    /* 0x30 */ BreathType starting_breath;
    /* 0x34 */ u32 starting_abilities;
    /* 0x38 */ bool skip_realm_intro_cutscenes;
    /* 0x39 */ bool skip_cutscene_button;
    /* 0x3A */ bool allow_teleport_to_hub;
    /* 0x3B */ bool allow_immediate_realm_access;

    // For detecting whether the gamestate should initialize.
    // Always the ASCII value "EBBE" when initialized.
    /* 0x3C */ u32 init;

    // Number of datasheets in this spreadsheet.
    // GUI_Shop only has 1 datasheet.
    /* 0x40 */ int xls_shop_sheetcount_ALWAYS_1;

    // Offset from here until the datasheet.
    // This will always be 4 bytes.
    /* 0x44 */ int xls_shop_sheet_offset_ALWAYS_4;

    // Number of rows in the datasheet.
    // This is the number of items in the shop (15 in vanilla).
    /* 0x48 */ int xls_shop_rowcount;

    // The entries in the datasheet, each representing a shop item.
    /* 0x4C */ xlsShoppingItem xls_shop_items[SHOP_TOTAL_NUM_ENTRIES];

    /* 0xCCC */ APSettings_TextEntry shop_text[SHOP_TOTAL_NUM_ENTRIES - SHOP_NUM_VANILLA_ENTRIES];
} APSettings;

extern APSettings g_gamestate_ap_settings;

#define AP_GAMESTATE_SHOP_SPREADSHEET_START ((void*)(&g_gamestate_ap_settings.xls_shop_sheetcount_ALWAYS_1))

#endif /* AP_SETTINGS_H */