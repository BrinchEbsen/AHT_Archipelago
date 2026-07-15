#include <util.h>
#include <shop_hooks.h>
#include <ap_settings.h>
#include <hashcodes.h>
#include <gametext.h>
#include <ap_keyring.h>
#include <igstdlib.h>
#include <gamestate.h>

void *SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook(
    SE_SpreadSheet *self, EXHashCode FileHash, EXHashCode SpreadSheetHash)
{
    // Shop isn't random, and doesn't use key rings
    // (use the vanilla shop list, but patch it a bit)
    if (!AP_GAMESTATE_SHOP_IS_RANDOMIZED && !AP_GAMESTATE_USE_KEY_RINGS) {
        void* data = (xlsShoppingItem*)SE_SpreadSheet__OpenSpreadSheet_FileHash(self, FileHash, SpreadSheetHash);
        
        // Change flame bomb availableflags to only allow purchase when fire breath is acquired
        xlsShoppingItem* items = OFFSET_PTR(xlsShoppingItem, data, 0xc);
        items[2].AvailableFlags |= ABILITY_AP_FIREBREATH;
        items[6].AvailableFlags |= ABILITY_AP_FIREBREATH;

        // Set teleport pass ticket to desired price
        items[14].cost[0] = TELEPORT_PASS_PRICE;
        items[14].cost[1] = TELEPORT_PASS_PRICE;
    
        return data;
    }

    // Shop isn't random, and uses key rings
    // (set up the shop in code)
    if (!AP_GAMESTATE_SHOP_IS_RANDOMIZED && AP_GAMESTATE_USE_KEY_RINGS) {
        if (g_gamestate_ap_settings.xls_shop_rowcount == 0) {
            initialize_vanilla_key_ring_shop();
        }
    }

    self->m_pSpreadSheet = AP_GAMESTATE_SHOP_SPREADSHEET_START;

    // If the row count is 0, the client probably forgot to write stuff there
    // Write a 1 just to prevent a crash
    if (g_gamestate_ap_settings.xls_shop_rowcount == 0) {
        g_gamestate_ap_settings.xls_shop_rowcount = 1;
    }

    return self->m_pSpreadSheet;
}

void GUI_Item__v_GetText_ReImplHook(GUI_Base* self, wchar16** pWide, char** pString)
{
    *pString = GUI_ITEM__STRING(self);
    *pWide = NULL;

    EXHashCode hash = GUI_ITEM__HASHCODE(self);
    
    // Injection of custom hashcode
    if ((hash & 0xFFFF0000) == AP_TEXT_ENTRY_HASHCODE_BASE) {
        int index = hash & 0xFFFF;
        *pWide = g_gamestate_ap_settings.shop_text[index].text;
        return;
    }

    if (hash != HT_Text_HASHCODE_BASE) {
        *pWide = GameText__GetText(&gGameText, hash, 0, 0);
    }

    wchar16* this_widestr = GUI_ITEM__WIDESTRING(self);
    if (this_widestr != NULL) {
        *pWide = this_widestr;
    }
}

int GUI_ShopItem__BuyItems_PreCallHook(GUI_ShopItem* self)
{
    if ((self->m_pItemData->ItemText & 0xFFFF0000) == AP_TEXT_ENTRY_HASHCODE_BASE) {
        int index = self->m_pItemData->ItemText & 0xFFFF;

        if (!AP_GAMESTATE_SHOP_IS_RANDOMIZED && AP_GAMESTATE_USE_KEY_RINGS) {
            set_u8_bitfield_value(g_gamestate_ap_settings.keyring_bitfield, index, true);
        } else {
            g_gamestate_ap_settings.shop_text[index].been_bought = true;
        }
    }
    
    s32 prevGems = gGameState.m_PlayerState.m_Gems;
    int result = GUI_ShopItem__BuyItems(self);
    
    // Revert gem subtraction if shop is in "unlock mode"
    if (g_gamestate_ap_settings.shop_unlock_mode) {
        gGameState.m_PlayerState.m_Gems = prevGems;
    }

    return result;
}

int GUI_ShopItem__IsAvailable_PreCallHook(GUI_ShopItem* self, Bool Buy)
{
    if ((self->m_pItemData->ItemText & 0xFFFF0000) == AP_TEXT_ENTRY_HASHCODE_BASE) {
        int index = self->m_pItemData->ItemText & 0xFFFF;
        
        if (!AP_GAMESTATE_SHOP_IS_RANDOMIZED && AP_GAMESTATE_USE_KEY_RINGS) {
            if (get_u8_bitfield_value(g_gamestate_ap_settings.keyring_bitfield, index)) {
                return 2;
            }
        } else {
            if (g_gamestate_ap_settings.shop_text[index].been_bought) {
                return 2;
            }
        }
    }

    return GUI_ShopItem__IsAvailable(self, Buy);
}

int GUI_ShopItem__GetCost_ReImplHook(GUI_ShopItem* self)
{
    if (self->m_pItemData == NULL) {
        return -1;
    }

    if (g_gamestate_ap_settings.shop_unlock_mode) {
        // Treat the cost variables as one 32-bit int
        return *((int*)&self->m_pItemData->cost[0]);
    } else {
        // Vanilla behavior
        if ((self->m_Flags & 4) != 0){
            return self->m_pItemData->cost[1];
        } else {
            return self->m_pItemData->cost[0];
        }
    }
}

void initialize_vanilla_key_ring_shop()
{
    xlsShoppingItem* items = g_gamestate_ap_settings.xls_shop_items;

    memcpy(items, g_vanilla_key_ring_shop_start_items, sizeof(xlsShoppingItem)*NUM_VANILLA_KEY_RING_SHOP_START_ITEMS);

    static int keyrings_start = NUM_VANILLA_KEY_RING_SHOP_START_ITEMS;

    for (int i = keyrings_start; i < keyrings_start+AP_NUM_KEYRINGS; i++) {
        int index = i - keyrings_start;

        items[i].Entity = HT_Entity_Lockpicker_Mag;
        items[i].File = HT_File_Panel;
        items[i].ItemText = AP_TEXT_ENTRY_HASHCODE_BASE + index;
        items[i].DescText = AP_TEXT_ENTRY_HASHCODE_BASE + index;
        items[i].cost[0] = g_ap_keyring_num_chests[index] * 500;
        items[i].cost[1] = g_ap_keyring_num_chests[index] * 625;
        items[i].Count = -1;
        items[i].Num = 0;
        items[i].AvailableFlags = 0;
        items[i].BroughtFlags = 0;

        APSettings_TextEntry* textentry = &g_gamestate_ap_settings.shop_text[index];
        textentry->been_bought = 0;
        
        int len = wstrlen(g_ap_keyring_shop_strings[index]);
        memcpy(textentry->text, g_ap_keyring_shop_strings[index], len*2);
    }

    g_gamestate_ap_settings.xls_shop_rowcount = keyrings_start+AP_NUM_KEYRINGS;
}

xlsShoppingItem g_vanilla_key_ring_shop_start_items[] = {
    {
        .Entity = HT_Entity_Shop_RightsOfPassage,
        .File = HT_File_Panel,
        .ItemText = HT_Text_ShoppingItem_RightsOfPassage,
        .DescText = HT_Text_ShoppingDesc_RightsOfPassage,
        .cost = { TELEPORT_PASS_PRICE, TELEPORT_PASS_PRICE },
        .Count = 1,
        .Num = 0,
        .AvailableFlags = ABILITY_BOUGHT_LOCK_PICK,
        .BroughtFlags = 0,
    },
    {
        .Entity = HT_Entity_SparxHit,
        .File = HT_File_Panel,
        .ItemText = HT_Text_ShoppingItem_SparxExtraHit,
        .DescText = HT_Text_ShoppingDesc_SparxExtraHit,
        .cost = { 500, 6250 },
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
    }
};
