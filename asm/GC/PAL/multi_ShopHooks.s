.memaddr 0x80229180
# Replace GUI_Shop spreadsheet open in GUI_ShopList::v_OnLoaded.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x8022af30
# Replace GUI_Shop spreadsheet open in PanelShop::GetAvailableFlags.
bl SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook

.memaddr 0x8022964c
# BuyItems call in GUI_ShopList::v_StateRunning
bl GUI_ShopItem__BuyItems_PreCallHook

.memaddr 0x80228044
# IsAvailable call in GUI_ShopItem::Init
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x80229ce0
# IsAvailable call in GUI_ShopList::v_StateRunning
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x802281dc
# IsAvailable call in GUI_ShopItem::Update
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x802281e8
# IsAvailable call in GUI_ShopItem::Update
bl GUI_ShopItem__IsAvailable_PreCallHook

.memaddr 0x80228988
# IsAvailable call in GUI_ShopItem::IncCount
bl GUI_ShopItem__IsAvailable_PreCallHook
