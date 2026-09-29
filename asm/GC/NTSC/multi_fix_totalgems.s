.memaddr 0x80200b7c
# Disable Gems and TotalGems write in SEMap_MiniGame::v_OnStart
nop
nop

.memaddr 0x80201ba0
# Disable Gems and TotalGems write in SEMap_MiniGame::v_OnClose
nop
nop

.memaddr 0x80201c40
# Force branch to be taken in SEMap_MiniGame::SetMiniGameComplete
# (to prevent the gem effect from playing)
li 11, -1

.memaddr 0x80201c74
# Disable Gems and TotalGems write in SEMap_MiniGame::SetMiniGameComplete
nop
nop

.memaddr 0x80201c84
# Disable GUI_Panel::PanelAddGems call in SEMap_MiniGame::SetMiniGameComplete
nop

.memaddr 0x802200cc
# Disable Gems and TotalGems write in SEMap_MiniGame::GUI_PanelItem::v_StateRunning
nop
nop
