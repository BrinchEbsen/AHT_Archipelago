.memaddr 0x80228b0c
# Replace GUI_Shop spreadsheet open in GUI_ShopList::v_OnLoaded.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x8022a8bc
# Replace GUI_Shop spreadsheet open in PanelShop::GetAvailableFlags.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook
