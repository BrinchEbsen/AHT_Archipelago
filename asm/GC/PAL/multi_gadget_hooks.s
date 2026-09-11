.memaddr 0x800e9050
# Disable supercharge cost check in GadgetPad::Update
cmpwi 3, 0

.memaddr 0x800e8320
# Disable supercharge cost check in GadgetPad::InitialiseStart
cmpwi 3, 0

.memaddr 0x800e8774
# Disable supercharge cost check in GadgetPad::CheckForLightGemChange
cmpwi 3, 0

.memaddr 0x800e90a8
# Disable invincibility cost check GadgetPad::Update
cmpwi 3, 0

.memaddr 0x800e83ac
# Disable invincibility cost check in GadgetPad::InitialiseStart
cmpwi 3, 0

.memaddr 0x800e8814
# Disable invincibility cost check in GadgetPad::CheckForLightGemChange
cmpwi 3, 0

.memaddr 0x800e8f84
# Spoof ball gadget cost check in GadgetPad::Update
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook

.memaddr 0x800e8944
# Spoof ball gadget cost check in GadgetPad::InitBallGadgetPad
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook

.memaddr 0x800e86c8
# Spoof ball gadget cost check in GadgetPad::CheckForLightGemChange
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook
