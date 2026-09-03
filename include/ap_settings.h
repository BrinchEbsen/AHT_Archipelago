#ifndef AP_SETTINGS_H
#define AP_SETTINGS_H
#include <types.h>
#include <player.h>
#include <playerstate.h>
#include <xls_shop.h>

#define AP_SETTINGS_LOCATIONS_BITFIELD_SIZE 0x50
#define AP_SETTINGS_KEYRINGS_BITFIELD_SIZE 0x2
#define AP_SETTINGS_SHOPPAD_BITFIELD_SIZE 0x5
#define AP_SETTINGS_INIT_MAGICVALUE 0x45424245 // 'EBBE' in ASCII :)

#define SHOP_NUM_VANILLA_ENTRIES 1
#define SHOP_NUM_CUSTOM_ENTRIES 60
#define SHOP_TOTAL_NUM_ENTRIES 61
// Base hashcode for custom shop text elements.
#define AP_TEXT_ENTRY_HASHCODE_BASE 0x28010000

#define AP_DEATHLINK_MODE_NONE      0
#define AP_DEATHLINK_MODE_SHIELDED  1
#define AP_DEATHLINK_MODE_FULL      2

#define AP_TELEPORT_MODE_VANILLA        0
#define AP_TELEPORT_MODE_TP_TO_HUB      1
#define AP_TELEPORT_MODE_SHOP_ANYWHERE  2

typedef enum DeathLinkReason
{
    /*  0 */ DLReason_None,             // No death (0)
    /*  1 */ DLReason_Default,          // Fallback value if type of death couldn't be figured out
    /*  2 */ DLReason_Spy_Default,      // Spyro normal death
    /*  3 */ DLReason_Spy_Water,        // Spyro death in water
    /*  4 */ DLReason_Spy_Fall,         // Spyro falls into bottomless pit
    /*  5 */ DLReason_Spy_Lava,         // Spyro on lava
    /*  6 */ DLReason_Spy_Swamp,        // Spyro in quicksand
    /*  7 */ DLReason_Spy_Squash,       // Spyro squashed
    /*  8 */ DLReason_Spy_Freeze,       // Spyro frozen
    /*  9 */ DLReason_Hun_Default,      // Hunter normal death
    /* 10 */ DLReason_Hun_Fall,         // Hunter fall into bottomless pit
    /* 11 */ DLReason_Hun_Drown,        // Hunter drown
    /* 12 */ DLReason_Hun_Squash,       // Hunter squashed
    /* 13 */ DLReason_Blk_Default,      // Blink normal death
    /* 14 */ DLReason_Blk_Fall,         // Blink fall into bottomless pit
    /* 15 */ DLReason_Blk_Lava,         // Blink on lava
    /* 16 */ DLReason_Blk_Drown,        // Blink drown
    /* 17 */ DLReason_Blk_Squash,       // Blink squashed
    /* 18 */ DLReason_Sgt_Default,      // Sgt. Byrd normal death (fallback)
    /* 19 */ DLReason_Sgt_WaterCrash,   // Sgt. Byrd crashed into water
    /* 20 */ DLReason_Sgt_LavaCrash,    // Sgt. Byrd crashed into lava
    /* 21 */ DLReason_Sgt_Fall,         // Sgt. Byrd fall into bottomless pit
    /* 22 */ DLReason_Spx_Default,      // Sparx death
    /* 23 */ DLReason_Ball_Default,     // Ball Gadget death
    /* 24 */ DLReason_Turret_R1,        // Turret minigame fail (realm 1)
    /* 25 */ DLReason_Turret_R2,        // Turret minigame fail (realm 2)
    /* 26 */ DLReason_Turret_R3,        // Turret minigame fail (realm 3)
    /* 27 */ DLReason_Turret_R4         // Turret minigame fail (realm 4)
} DeathLinkReason;

#define TELEPORT_PASS_PRICE 0

typedef struct APSettings_TextEntry
{
    /* 0x0 */ bool been_bought;
    /* 0x1 */ u8 padding;
    /* 0x2 */ wchar16 text[48];
} APSettings_TextEntry; // Size: 0x62

/*
 * Read the wiki for this mod for a detailed explanation of the settings:
 * https://github.com/BrinchEbsen/AHT_Archipelago/wiki
 */

typedef struct APSettings {
    u8 location_bitfield[AP_SETTINGS_LOCATIONS_BITFIELD_SIZE];
    u8 keyring_bitfield[AP_SETTINGS_KEYRINGS_BITFIELD_SIZE];
    u8 shoppad_bitfield[AP_SETTINGS_SHOPPAD_BITFIELD_SIZE];
    u8 num_gem_packs_received;
    u8 num_lock_picks_received;
    u8 num_fire_ammo_received;
    u8 num_electric_ammo_received;
    u8 num_water_ammo_received;
    u8 num_ice_ammo_received;
    u8 deathlink_ingoing;
    u8 deathlink_outgoing;
    u8 deathlink_deaths_before_send;
    u8 deathlink_death_counter;
    bool infinite_butterfly_jar;
    bool infinite_double_gem;
    bool fireworks_are_randomized;
    bool randomize_shop;
    bool use_key_rings;

    bool skip_cutscene_button;
    u8 instant_teleport_mode;
    bool disable_popups;
    bool instant_elevators;

    u8 starting_realm;
    bool realm_access[4];

    bool patch_been_written_to;
    u32 mw_seed;

    // For detecting whether the gamestate should initialize.
    // Always the ASCII value "EBBE" when initialized.
    u32 init;

    u8 boss_costs[4];
    u8 lg_door_costs[4];
    u8 ball_gadget_cost;
    u8 invincibility_cost;
    u8 supercharge_cost;
    bool boss_easy_mode[4];

    bool shop_unlock_mode;

    bool teleport_anywhere;

    bool unlock_all_shops;

    bool disable_shop_pad_proximity_activate;
    bool disable_main_shop_always_available;

    int total_gems_in_logic;
    int total_gems_available;

    bool ut_enabled;

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

    APSettings_TextEntry shop_text[SHOP_NUM_CUSTOM_ENTRIES];
} APSettings;

// The gamestate area settings. These are used while the game is being played.
// The translation unit containing this variable is held in the save's current game state,
// and it is therefore persisted on the memory card.
// Specifically it's held 0x2000 bytes into the save's "bitheap", which contains states for
// the minimap coverage and trigger preserved states. A 100% playthrough will only fill this
// 1/3rd of the way up, so we're free to make use of the latter half of its 0x4000 bytes.
// We do also have to fix a bug with the bitheap allocate function which accidentally clears
// way more bits than it's meant to, which could corrupt our data.
// (see the hook SE_BitHeap__Allocate__FixBug.s)
extern APSettings g_gamestate_ap_settings;

#define AP_GAMESTATE_SHOP_SPREADSHEET_START ((void*)(&g_gamestate_ap_settings.xls_shop_sheetcount_ALWAYS_1))
#define AP_GAMESTATE_SHOP_IS_RANDOMIZED (g_gamestate_ap_settings.randomize_shop)
#define AP_GAMESTATE_USE_KEY_RINGS (g_gamestate_ap_settings.use_key_rings)

#endif /* AP_SETTINGS_H */