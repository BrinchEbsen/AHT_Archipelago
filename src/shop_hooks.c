#include <util.h>
#include <shop_hooks.h>
#include <ap_settings.h>
#include <hashcodes.h>
#include <gametext.h>
#include <ap_keyring.h>
#include <igstdlib.h>

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
        *pString = g_gamestate_ap_settings.shop_text[index].text;
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
    
    return GUI_ShopItem__BuyItems(self);
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
        return 0;
    }

    return GUI_ShopItem__IsAvailable(self, Buy);
}

void initialize_vanilla_key_ring_shop()
{
    xlsShoppingItem* items = g_gamestate_ap_settings.xls_shop_items;

    items[0].Entity = HT_Entity_Shop_RightsOfPassage;
    items[0].File = HT_File_Panel;
    items[0].ItemText = HT_Text_ShoppingItem_RightsOfPassage;
    items[0].DescText = HT_Text_ShoppingDesc_RightsOfPassage;
    items[0].cost[0] = 100;
    items[0].cost[1] = 100;
    items[0].Count = 1;
    items[0].Num = 0;
    items[0].AvailableFlags = ABILITY_BOUGHT_LOCK_PICK;
    items[0].BroughtFlags = 0;

    items[1].Entity = HT_Entity_SparxHit;
    items[1].File = HT_File_Panel;
    items[1].ItemText = HT_Text_ShoppingItem_SparxExtraHit;
    items[1].DescText = HT_Text_ShoppingDesc_SparxExtraHit;
    items[1].cost[0] = 5000;
    items[1].cost[1] = 6250;
    items[1].Count = 1;
    items[1].Num = 0;
    items[1].AvailableFlags = ABILITY_BOUGHT_LOCK_PICK;
    items[1].BroughtFlags = ABILITY_HIT_POINT_UPGRADE;

    items[2].Entity = HT_Entity_FlameBreath;
    items[2].File = HT_File_Panel;
    items[2].ItemText = HT_Text_ShoppingItem_FireAmmo;
    items[2].DescText = HT_Text_ShoppingDesc_FireAmmo;
    items[2].cost[0] = 50;
    items[2].cost[1] = 62;
    items[2].Count = -1;
    items[2].Num = 0;
    items[2].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_AP_FIREBREATH;
    items[2].BroughtFlags = 0x8;

    items[3].Entity = HT_Entity_ElectricBreath;
    items[3].File = HT_File_Panel;
    items[3].ItemText = HT_Text_ShoppingItem_ElectricAmmo;
    items[3].DescText = HT_Text_ShoppingDesc_ElectricAmmo;
    items[3].cost[0] = 250;
    items[3].cost[1] = 312;
    items[3].Count = -1;
    items[3].Num = 0;
    items[3].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ELECTRIC_BREATH;
    items[3].BroughtFlags = 0x8;

    items[4].Entity = HT_Entity_WaterBreath;
    items[4].File = HT_File_Panel;
    items[4].ItemText = HT_Text_ShoppingItem_WaterAmmo;
    items[4].DescText = HT_Text_ShoppingDesc_WaterAmmo;
    items[4].cost[0] = 50;
    items[4].cost[1] = 62;
    items[4].Count = -1;
    items[4].Num = 0;
    items[4].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_WATER_BREATH;
    items[4].BroughtFlags = 0x8;

    items[5].Entity = HT_Entity_IceBreath;
    items[5].File = HT_File_Panel;
    items[5].ItemText = HT_Text_ShoppingItem_IceAmmo;
    items[5].DescText = HT_Text_ShoppingDesc_IceAmmo;
    items[5].cost[0] = 100;
    items[5].cost[1] = 125;
    items[5].Count = -1;
    items[5].Num = 0;
    items[5].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ICE_BREATH;
    items[5].BroughtFlags = 0x8;

    items[6].Entity = HT_Entity_FlameBreathMag;
    items[6].File = HT_File_Panel;
    items[6].ItemText = HT_Text_ShoppingItem_FireMag;
    items[6].DescText = HT_Text_ShoppingDesc_FireMag;
    items[6].cost[0] = 500;
    items[6].cost[1] = 625;
    items[6].Count = -1;
    items[6].Num = 5;
    items[6].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_AP_FIREBREATH;
    items[6].BroughtFlags = 0;

    items[7].Entity = HT_Entity_ElectricBreathMag;
    items[7].File = HT_File_Panel;
    items[7].ItemText = HT_Text_ShoppingItem_ElectricMag;
    items[7].DescText = HT_Text_ShoppingDesc_ElectricMag;
    items[7].cost[0] = 1000;
    items[7].cost[1] = 1250;
    items[7].Count = -1;
    items[7].Num = 1;
    items[7].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ELECTRIC_BREATH;
    items[7].BroughtFlags = 0;

    items[8].Entity = HT_Entity_WaterBreathMag;
    items[8].File = HT_File_Panel;
    items[8].ItemText = HT_Text_ShoppingItem_WaterMag;
    items[8].DescText = HT_Text_ShoppingDesc_WaterMag;
    items[8].cost[0] = 250;
    items[8].cost[1] = 312;
    items[8].Count = -1;
    items[8].Num = 10;
    items[8].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_WATER_BREATH;
    items[8].BroughtFlags = 0;

    items[9].Entity = HT_Entity_IceBreathMag;
    items[9].File = HT_File_Panel;
    items[9].ItemText = HT_Text_ShoppingItem_IceMag;
    items[9].DescText = HT_Text_ShoppingDesc_IceMag;
    items[9].cost[0] = 750;
    items[9].cost[1] = 937;
    items[9].Count = -1;
    items[9].Num = 2;
    items[9].AvailableFlags = 
                ABILITY_BOUGHT_LOCK_PICK |
                ABILITY_ICE_BREATH;
    items[9].BroughtFlags = 0;

    items[10].Entity = HT_Entity_FullHealth;
    items[10].File = HT_File_Panel;
    items[10].ItemText = HT_Text_ShoppingItem_FullHealth;
    items[10].DescText = HT_Text_ShoppingDesc_FullHealth;
    items[10].cost[0] = 1500;
    items[10].cost[1] = 1875;
    items[10].Count = 1;
    items[10].Num = 0;
    items[10].AvailableFlags = ABILITY_BOUGHT_LOCK_PICK;
    items[10].BroughtFlags = ABILITY_BUTTERFLY_JAR;

    items[11].Entity = HT_Entity_Shop_DoubleGemVal;
    items[11].File = HT_File_Panel;
    items[11].ItemText = HT_Text_ShoppingItem_DoubleValue;
    items[11].DescText = HT_Text_ShoppingDesc_DoubleValue;
    items[11].cost[0] = 1000;
    items[11].cost[1] = 1250;
    items[11].Count = 1;
    items[11].Num = 0;
    items[11].AvailableFlags = ABILITY_BOUGHT_LOCK_PICK;
    items[11].BroughtFlags = ABILITY_DOUBLE_GEM;

    items[12].Entity = HT_Entity_Shop_HornDive;
    items[12].File = HT_File_Panel;
    items[12].ItemText = HT_Text_ShoppingItem_HornDive;
    items[12].DescText = HT_Text_ShoppingDesc_HornDive;
    items[12].cost[0] = 10000;
    items[12].cost[1] = 12500;
    items[12].Count = 1;
    items[12].Num = 0;
    items[12].AvailableFlags = ABILITY_BOUGHT_LOCK_PICK;
    items[12].BroughtFlags = ABILITY_HORN_DIVE_UPGRADE;

    static int keyrings_start = 13;

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
        strcpy(textentry->text, g_ap_keyring_shop_strings[index]);
    }

    g_gamestate_ap_settings.xls_shop_rowcount = keyrings_start+AP_NUM_KEYRINGS;
}
