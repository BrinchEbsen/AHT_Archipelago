.memaddr 0x
# Disable supercharge cost check in GadgetPad::Update
cmpwi 3, 0

.memaddr 0x
# Disable supercharge cost check in GadgetPad::InitialiseStart
cmpwi 3, 0

.memaddr 0x
# Disable supercharge cost check in GadgetPad::CheckForLightGemChange
cmpwi 3, 0

.memaddr 0x
# Disable invincibility cost check GadgetPad::Update
cmpwi 3, 0

.memaddr 0x
# Disable invincibility cost check in GadgetPad::InitialiseStart
cmpwi 3, 0

.memaddr 0x
# Disable invincibility cost check in GadgetPad::CheckForLightGemChange
cmpwi 3, 0

.memaddr 0x
# Spoof ball gadget cost check in GadgetPad::Update
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook

.memaddr 0x
# Spoof ball gadget cost check in GadgetPad::InitBallGadgetPad
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook

.memaddr 0x
# Spoof ball gadget cost check in GadgetPad::CheckForLightGemChange
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook
