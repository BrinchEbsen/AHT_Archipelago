#ifndef SHOP_HOOKS_H
#define SHOP_HOOKS_H
#include <types.h>
#include <spreadsheet.h>
#include <gui_base.h>
#include <xls_shop.h>

typedef struct GUI_ShopItem
{
    xlsShoppingItem* m_pItemData;
    int m_Count;
    int m_Available;
    int m_Flags;
    int m_Index;
    int m_Items;
    float m_Accel;
    void* m_pParent;
    void* m_pAnimator;
    s32 m_TeleportMapIndex;
    s32 m_TeleportTrigIndex;
} GUI_ShopItem;

#define GUI_ITEM__HASHCODE(self)    OFFSET_VAL(EXHashCode, self, 0x290)
#define GUI_ITEM__STRING(self)      OFFSET_VAL(char*, self, 0x2a8)
#define GUI_ITEM__WIDESTRING(self)  OFFSET_VAL(wchar16*, self, 0x2ac)

extern void* SE_SpreadSheet__OpenSpreadSheet_FileHash(
    SE_SpreadSheet* self, EXHashCode FileHash, EXHashCode SpreadSheetHash);

void* SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook(
    SE_SpreadSheet* self, EXHashCode FileHash, EXHashCode SpreadSheetHash);

void GUI_Item__v_GetText_ReImplHook(GUI_Base* self, wchar16** pWide, char** pString);

extern int GUI_ShopItem__BuyItems(GUI_ShopItem* self);
int GUI_ShopItem__BuyItems_PreCallHook(GUI_ShopItem* self);

extern int GUI_ShopItem__IsAvailable(GUI_ShopItem* self, Bool Buy);
int GUI_ShopItem__IsAvailable_PreCallHook(GUI_ShopItem* self, Bool Buy);

#endif /* SHOP_HOOKS_H */