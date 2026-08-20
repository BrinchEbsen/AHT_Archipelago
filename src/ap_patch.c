#include <ap_patch.h>
#include <playerstate.h>
#include <hashcodes.h>

// #define USE_VANILLA_SHOP

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

    #ifdef AP_QUICK_START
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

    #ifdef AP_QUICK_START
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

    #ifdef AP_QUICK_START
    .ut_enabled = true,
    #else
    .ut_enabled = false,
    #endif

    // SHOP ITEMS
    .xls_shop_sheetcount_ALWAYS_1 = 1,
    .xls_shop_sheet_offset_ALWAYS_4 = 4,
    #ifdef USE_VANILLA_SHOP
    .xls_shop_rowcount = 15,
    .xls_shop_items = {
        {
            .Entity = HT_Entity_Lockpicker,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_SparxLockPicker,
            .DescText = HT_Text_ShoppingDesc_SparxLockPicker,
            .cost = { 500, 625 },
            .Count = -1,
            .Num = 0,
            .AvailableFlags = 0,
            .BroughtFlags = ABILITY_BOUGHT_LOCK_PICK
        },
        {
            .Entity = HT_Entity_SparxHit,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_SparxExtraHit,
            .DescText = HT_Text_ShoppingDesc_SparxExtraHit,
            .cost = { 5000, 6250 },
            .Count = 1,
            .Num = 0,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = ABILITY_HIT_POINT_UPGRADE
        },
        {
            .Entity = HT_Entity_FlameBreath,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_FireAmmo,
            .DescText = HT_Text_ShoppingDesc_FireAmmo,
            .cost = { 50, 62 },
            .Count = -1,
            .Num = 0,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_AP_FIREBREATH,
            .BroughtFlags = 0x8
        },
        {
            .Entity = HT_Entity_ElectricBreath,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_ElectricAmmo,
            .DescText = HT_Text_ShoppingDesc_ElectricAmmo,
            .cost = { 250, 312 },
            .Count = -1,
            .Num = 0,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ELECTRIC_BREATH,
            .BroughtFlags = 0x8
        },
        {
            .Entity = HT_Entity_WaterBreath,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_WaterAmmo,
            .DescText = HT_Text_ShoppingDesc_WaterAmmo,
            .cost = { 50, 62 },
            .Count = -1,
            .Num = 0,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_WATER_BREATH,
            .BroughtFlags = 0x8
        },
        {
            .Entity = HT_Entity_IceBreath,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_IceAmmo,
            .DescText = HT_Text_ShoppingDesc_IceAmmo,
            .cost = { 100, 125 },
            .Count = -1,
            .Num = 0,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ICE_BREATH,
            .BroughtFlags = 0x8
        },
        {
            .Entity = HT_Entity_FlameBreathMag,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_FireMag,
            .DescText = HT_Text_ShoppingDesc_FireMag,
            .cost = { 500, 625 },
            .Count = -1,
            .Num = 5,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_AP_FIREBREATH,
            .BroughtFlags = 0
        },
        {
            .Entity = HT_Entity_ElectricBreathMag,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_ElectricMag,
            .DescText = HT_Text_ShoppingDesc_ElectricMag,
            .cost = { 1000, 1250 },
            .Count = -1,
            .Num = 1,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ELECTRIC_BREATH,
            .BroughtFlags = 0
        },
        {
            .Entity = HT_Entity_WaterBreathMag,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_WaterMag,
            .DescText = HT_Text_ShoppingDesc_WaterMag,
            .cost = { 250, 312 },
            .Count = -1,
            .Num = 10,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_WATER_BREATH,
            .BroughtFlags = 0
        },
        {
            .Entity = HT_Entity_IceBreathMag,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_IceMag,
            .DescText = HT_Text_ShoppingDesc_IceMag,
            .cost = { 750, 937 },
            .Count = -1,
            .Num = 2,
            .AvailableFlags =
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ICE_BREATH,
            .BroughtFlags = 0
        },
        {
            .Entity = HT_Entity_Lockpicker_Mag,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_KeyChain,
            .DescText = HT_Text_ShoppingDesc_KeyChain,
            .cost = { 5000, 6250 },
            .Count = 1,
            .Num = 2,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = 0
        },
        {
            .Entity = HT_Entity_FullHealth,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_FullHealth,
            .DescText = HT_Text_ShoppingDesc_FullHealth,
            .cost = { 1500, 1875 },
            .Count = 1,
            .Num = 0,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = ABILITY_BUTTERFLY_JAR
        },
        {
            .Entity = HT_Entity_Shop_DoubleGemVal,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_DoubleValue,
            .DescText = HT_Text_ShoppingDesc_DoubleValue,
            .cost = { 1000, 1250 },
            .Count = 1,
            .Num = 0,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = ABILITY_DOUBLE_GEM
        },
        {
            .Entity = HT_Entity_Shop_HornDive,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_HornDive,
            .DescText = HT_Text_ShoppingDesc_HornDive,
            .cost = { 10000, 12500 },
            .Count = 1,
            .Num = 0,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = ABILITY_HORN_DIVE_UPGRADE
        },
        {
            .Entity = HT_Entity_Shop_RightsOfPassage,
            .File = HT_File_Panel,
            .ItemText = HT_Text_ShoppingItem_RightsOfPassage,
            .DescText = HT_Text_ShoppingDesc_RightsOfPassage,
            .cost = { 100, 100 },
            .Count = 1,
            .Num = 0,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = 0
        }
    }
    #else
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
        // ,{
        //     .Entity = HT_Entity_Shop_TeleportMainShop,
        //     .File = HT_File_Panel,
        //     .ItemText = AP_TEXT_ENTRY_HASHCODE_BASE,
        //     .DescText = AP_TEXT_ENTRY_HASHCODE_BASE,
        //     .cost = { 0x60, 0x0 }, // 6,291,456
        //     .Count = 1,
        //     .Num = 0,
        //     .AvailableFlags = 0,
        //     .BroughtFlags = 0
        // }
    }
    
    // ,.shop_text = {
    //     {
    //         .been_bought = false,
    //         .padding = 0,
    //         .text = u"Test shop item"
    //     }
    // }
    #endif /* USE_VANILLA_SHOP */
};