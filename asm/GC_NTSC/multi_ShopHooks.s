.memaddr 0x80228b0c
# Replace GUI_Shop spreadsheet open in GUI_ShopList::v_OnLoaded.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x8022a8bc
# Replace GUI_Shop spreadsheet open in PanelShop::GetAvailableFlags.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x80228fd8
# BuyItems call in GUI_ShopList::v_StateRunning
bl GUI_ShopItem__BuyItems_PreCallHook

.memaddr 0x802279d0
# IsAvailable call in GUI_ShopItem::Init
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x8022966c
# IsAvailable call in GUI_ShopList::v_StateRunning
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x80227b68
# IsAvailable call in GUI_ShopItem::Update
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x80227b74
# IsAvailable call in GUI_ShopItem::Update
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x80228314
# IsAvailable call in GUI_ShopItem::IncCount
bl GUI_ShopItem__IsAvailable_PreCallHook
