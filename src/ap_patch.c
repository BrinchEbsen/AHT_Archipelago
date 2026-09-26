#include <ap_patch.h>
#include <playerstate.h>
#include <hashcodes.h>

APSettings g_patch_ap_settings = {
    .location_bitfield = {0},
    .keyring_bitfield = {0},
    .shoppad_bitfield = {0},
    .num_gem_packs_received = 0,
    .num_fire_ammo_received = 0,
    .num_electric_ammo_received = 0,
    .num_water_ammo_received = 0,
    .num_ice_ammo_received = 0,
    .deathlink_ingoing = AP_DEATHLINK_MODE_NONE,
    .deathlink_outgoing = DLReason_None,
    .deathlink_deaths_before_send = 1,
    .deathlink_death_counter = 0,
    .infinite_butterfly_jar = false,
    .infinite_double_gem = false,
    .fireworks_are_randomized = false,
    .randomize_shop = false,
    .use_key_rings = false,

    #if AP_DEBUG_QUICK_START!=0
    .skip_cutscene_button = true,
    .instant_teleport_mode = AP_TELEPORT_MODE_SHOP_ANYWHERE,
    .disable_popups = true,
    .instant_elevators = true,
    .starting_realm = 0,
    .realm_access = {
        true,
        true,
        true,
        true
    },

    .patch_been_written_to = true,

    .mw_seed = 0x69696969,
    #else
    .skip_cutscene_button = false,
    .instant_teleport_mode = AP_TELEPORT_MODE_VANILLA,
    .disable_popups = false,
    .instant_elevators = false,
    .starting_realm = 0,
    .realm_access = {
        false,
        false,
        false,
        false
    },

    .patch_been_written_to = false,

    .mw_seed = 0,
    #endif
    
    .init = 0,
    
    // BOSS/DOOR COSTS
    .boss_costs = {
        10,
        20,
        30,
        40
    },
    .lg_door_costs = {
        70,
        20,
        95,
        45
    },
    .ball_gadget_cost = 8,
    .invincibility_cost = 24,
    .supercharge_cost = 40,

    .boss_easy_mode = {
        false,
        false,
        false,
        false
    },

    .shop_unlock_mode = false,
    .display_gem_stats = false,

    #if AP_DEBUG_QUICK_START!=0
    .teleport_anywhere = true,
    .unlock_all_shops = true,
    #else
    .teleport_anywhere = false,
    .unlock_all_shops = false,
    #endif

    .disable_shop_pad_proximity_activate = false,
    .disable_main_shop_always_available = false,
    
    .total_gems_in_logic = 0,
    .total_gems_available = 0,

    #if AP_DEBUG_QUICK_START!=0
    .ut_enabled = true,
    #else
    .ut_enabled = false,
    #endif

    .trap = 0,
    .trap_data = 0,
    .trap_counters = {0},

    .minigame_blink_config = MinigameConfig_Normal,
    .minigame_sparx_config = MinigameConfig_Normal,
    .minigame_turret_config = MinigameConfig_Normal,
    .minigame_sgtbyrd_config = MinigameConfig_Normal,

    // Custom shop item spreadsheet
    .xls_shop_sheetcount_ALWAYS_1 = 1,
    .xls_shop_sheet_offset_ALWAYS_4 = 4,
    .xls_shop_rowcount = 0,
    .xls_shop_items = {
        {
            .Entity = HT_Entity_Shop_RightsOfPassage,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_RightsOfPassage,
            .DescText = HT_Text_ShoppingDesc_RightsOfPassage,
            .cost = { TELEPORT_PASS_PRICE, TELEPORT_PASS_PRICE },
            .Count = 1,
            .Num = 0,
            .AvailableFlags = 0,
            .BroughtFlags = 0
        }
    }
};
