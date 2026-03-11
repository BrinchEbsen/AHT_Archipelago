#ifndef SHOP_HOOKS_H
#define SHOP_HOOKS_H
#include <types.h>
#include <spreadsheet.h>
#include <gui_base.h>

#define GUI_ITEM__HASHCODE(self)    OFFSET_VAL(EXHashCode, self, 0x290)
#define GUI_ITEM__STRING(self)      OFFSET_VAL(char*, self, 0x2a8)
#define GUI_ITEM__WIDESTRING(self)  OFFSET_VAL(wchar16*, self, 0x2ac)

extern void* SE_SpreadSheet__OpenSpreadSheet_FileHash(
    SE_SpreadSheet* self, EXHashCode FileHash, EXHashCode SpreadSheetHash);

void* SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook(
    SE_SpreadSheet* self, EXHashCode FileHash, EXHashCode SpreadSheetHash);

void GUI_Item__v_GetText_ReImplHook(GUI_Base* self, wchar16** pWide, char** pString);

#endif /* SHOP_HOOKS_H */