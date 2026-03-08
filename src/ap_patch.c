#include <ap_patch.h>
#include <playerstate.h>
#include <hashcodes.h>

APSettings g_patch_ap_settings = {
    .location_bitfield = {0},
    .starting_breath = fire,
    .starting_abilities = ABILITY_AP_FIREBREATH | ABILITY_AP_CHARGE | ABILITY_AP_GLIDE | ABILITY_AP_SWIM,
    .free_realm_travel_enable = false,
    .skip_realm_intro_cutscenes = false,
    .skip_cutscene_button = true,
    .allow_teleport_to_hub = true,
    .init = 0,

    // SHOP ITEMS
    .xls_shop_sheetcount_ALWAYS_1 = 1,
    .xls_shop_sheet_offset_ALWAYS_4 = 4,
    .xls_shop_rowcount = 16,
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
        },

        {
            .Entity = HT_Entity_DragonEgg,
            .File = HT_File_CommonPickups,
            .ItemText = AP_TEXT_ENTRY_HASHCODE_BASE + 0,
            .DescText = AP_TEXT_ENTRY_HASHCODE_BASE + 0,
            .cost = { 100, 100 },
            .Count = -1,
            .Num = 0,
            .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
            .BroughtFlags = 0
        }
    },

    .shop_text = {
        /* 0 */ { .text = "Muh buh dwagon egg" }
    }
};