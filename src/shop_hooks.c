#include <shop_hooks.h>
#include <ap_settings.h>

void *SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook(
    SE_SpreadSheet *self, EXHashCode FileHash, EXHashCode SpreadSheetHash)
{
    self->m_pSpreadSheet = AP_GAMESTATE_SHOP_SPREADSHEET_START;
    return self->m_pSpreadSheet;
}
