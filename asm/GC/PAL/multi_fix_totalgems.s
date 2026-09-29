.memaddr 0x80201100
# Disable Gems and TotalGems write in SEMap_MiniGame::v_OnStart
nop
nop

.memaddr 0x80202124
# Disable Gems and TotalGems write in SEMap_MiniGame::v_OnClose
nop
nop

.memaddr 0x802021c4
# Force branch to be taken in SEMap_MiniGame::SetMiniGameComplete
# (to prevent the gem effect from playing)
li 11, -1

.memaddr 0x802021f8
# Disable Gems and TotalGems write in SEMap_MiniGame::SetMiniGameComplete
nop
nop

.memaddr 0x80202208
# Disable GUI_Panel::PanelAddGems call in SEMap_MiniGame::SetMiniGameComplete
nop

.memaddr 0x8022061c
# Disable Gems and TotalGems write in SEMap_MiniGame::GUI_PanelItem::v_StateRunning
nop
nop
