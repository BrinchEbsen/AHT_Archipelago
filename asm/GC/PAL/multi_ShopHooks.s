.memaddr 0x
# Replace GUI_Shop spreadsheet open in GUI_ShopList::v_OnLoaded.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x
# Replace GUI_Shop spreadsheet open in PanelShop::GetAvailableFlags.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x
# BuyItems call in GUI_ShopList::v_StateRunning
bl GUI_ShopItem__BuyItems_PreCallHook

.memaddr 0x
# IsAvailable call in GUI_ShopItem::Init
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x
# IsAvailable call in GUI_ShopList::v_StateRunning
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x
# IsAvailable call in GUI_ShopItem::Update
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x
# IsAvailable call in GUI_ShopItem::Update
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x
# IsAvailable call in GUI_ShopItem::IncCount
bl GUI_ShopItem__IsAvailable_PreCallHook
