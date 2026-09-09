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

typedef enum TrapType
{
    TrapType_MoneyBagsSpamCall,     // 1
    TrapType_ReversedControls,      // 2
    TrapType_NUM
} TrapType;

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

/// @brief Struct holding the settings and AP-related state of an AP playthrough.
/// 
/// Held in the patch area (`g_patch_ap_settings`) for initial settings written by the client.
/// 
/// Held in the gamestate area (`g_gamestate_ap_settings`) for the state of the current save.
typedef struct APSettings {

    /// @brief One long bitfield for every location in the multiworld.
    /// Every element is stored as two bits. The first is 1 if the item
    /// has been collected, and the second is 1 if it's deemed "reachable".
    u8 location_bitfield[AP_SETTINGS_LOCATIONS_BITFIELD_SIZE];

    /// @brief A bitfield for which of the 14 keyrings have been obtained in this save.
    u8 keyring_bitfield[AP_SETTINGS_KEYRINGS_BITFIELD_SIZE];

    /// @brief A bitfield for which of the 37 shop pads are enabled in this save.
    u8 shoppad_bitfield[AP_SETTINGS_SHOPPAD_BITFIELD_SIZE];

    /// @brief A value used by the client to keep track of the amount of gem packs obtained on this savefile.
    u8 num_gem_packs_received;

    /// @brief A value used by the client to keep track of the amount of lock picks obtained on this savefile.
    u8 num_lock_picks_received;

    /// @brief A value used by the client to keep track of the amount of fire bombs obtained on this savefile.
    u8 num_fire_ammo_received;

    /// @brief A value used by the client to keep track of the amount of electric missiles obtained on this savefile.
    u8 num_electric_ammo_received;

    /// @brief A value used by the client to keep track of the amount of water bombs obtained on this savefile.
    u8 num_water_ammo_received;

    /// @brief A value used by the client to keep track of the amount of ice missiles obtained on this savefile.
    u8 num_ice_ammo_received;

    /// @brief The ingoing deathlink signal. Set to 1 or 2 by the client to indicate a deathlink has been
    /// received and the game should kill the player.
    u8 deathlink_ingoing;

    /// @brief The outgoing deathlink signal. Set to a non-zero value by the game if the player has died enough times.
    u8 deathlink_outgoing;

    /// @brief The amount of times the player has to die before the outgoing signal is set.
    u8 deathlink_deaths_before_send;

    /// @brief Counter to keep track of the number of deaths the player has had since the last outgoing deathlink.
    u8 deathlink_death_counter;

    /// @brief Give the player a butterfly jar every time they die and respawn.
    bool infinite_butterfly_jar;

    /// @brief Turn on the double gem powerup permanently.
    bool infinite_double_gem;
    
    /// @brief Whether fireworks are randomized.
    bool fireworks_are_randomized;

    /// @brief Whether the shop is randomized.
    bool randomize_shop;

    /// @brief Whether key rings are used.
    bool use_key_rings;

    /// @brief Whether the cutscenes can be skipped with a button press.
    bool skip_cutscene_button;

    /// @brief The type of convenience option to present on the pause menu.
    ///
    /// - 0: None
    ///
    /// - 1: Teleport to HUB
    ///
    /// - 2: Shop anywhere
    u8 instant_teleport_mode;

    /// @brief Disable the tutorial pop-ups (always enabled).
    bool disable_popups;

    /// @brief Teleport the player to the top/bottom of the elevators when the player interacts with them.
    bool instant_elevators;

    /// @brief The realm the player should start this save in.
    u8 starting_realm;

    /// @brief Which realms the player has access to from the realm teleporter.
    bool realm_access[4];

    /// @brief Whether the patch struct has been written to by the client, and it's safe to copy to gamestate.
    bool patch_been_written_to;

    /// @brief The lower 4 bytes of the multiworld seed, to check for mismatches.
    u32 mw_seed;

    /// @brief For detecting whether the gamestate should initialize. Always the ASCII value "EBBE" when initialized.
    u32 init;

    /// @brief The Dark Gem costs for the barriers for each of the 4 bosses.
    u8 boss_costs[4];

    /// @brief The Light Gem costs for each of the 4 light gem doors.
    u8 lg_door_costs[4];

    /// @brief The Light Gem cost of the ball gadget.
    u8 ball_gadget_cost;

    /// @brief The Light Gem cost of the invincibility gadget.
    u8 invincibility_cost;

    /// @brief The Light Gem cost of the supercharge gadget.
    u8 supercharge_cost;

    /// @brief Whether the "boss easy mode" should be set for each of the 4 bosses.
    bool boss_easy_mode[4];

    /// @brief Set the shop items to progressively "unlock" by gem count instead of being bought.
    bool shop_unlock_mode;

    /// @brief Make the shop pad teleport ticket not limited to within the realm the player is in.
    bool teleport_anywhere;

    /// @brief Immediately unlock every shop pad teleport location from the start of the game.
    bool unlock_all_shops;

    /// @brief Disables the behavior where the game unlocks a shop pad for teleporting when you get close to it.
    bool disable_shop_pad_proximity_activate;
    
    /// @brief Disables the behavior where a realm's main shop is always selectable on the shop teleport menu.
    bool disable_main_shop_always_available;
    
    /// @brief The number of gems the player is expected to have logic-wise.
    int total_gems_in_logic;
    
    /// @brief The total number of gems the player has access to, logic-wise.
    int total_gems_available;

    /// @brief Whether the client has access to UniversalTracker.
    bool ut_enabled;

    /// @brief Which trap to initiate.
    u8 trap;
    
    /// @brief A generic slot for any parameters the trap signaled in `trap` might need.
    s32 trap_data;

    /// @brief Number of datasheets in this spreadsheet.
    /// GUI_Shop only has 1 datasheet.
    int xls_shop_sheetcount_ALWAYS_1;

    /// @brief Offset from here until the datasheet.
    /// This will always be 4 bytes.
    int xls_shop_sheet_offset_ALWAYS_4;

    /// @brief Number of rows in the datasheet.
    /// This is the number of items in the shop (15 in vanilla).
    int xls_shop_rowcount;

    /// @brief The entries in the datasheet, each representing a shop item.
    xlsShoppingItem xls_shop_items[SHOP_TOTAL_NUM_ENTRIES];

    /// @brief Properties and text of the custom shop items in `xls_shop_items`.
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