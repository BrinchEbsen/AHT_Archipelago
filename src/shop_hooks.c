#include <shop_hooks.h>
#include <ap_settings.h>
#include <hashcodes.h>
#include <gametext.h>

// #define AP_READ_CUSTOM_SPREADSHEET

void *SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook(
    SE_SpreadSheet *self, EXHashCode FileHash, EXHashCode SpreadSheetHash)
{
    #ifdef AP_READ_CUSTOM_SPREADSHEET
    self->m_pSpreadSheet = AP_GAMESTATE_SHOP_SPREADSHEET_START;
    return self->m_pSpreadSheet;
    #else
    return SE_SpreadSheet__OpenSpreadSheet_FileHash(self, FileHash, SpreadSheetHash);
    #endif
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
