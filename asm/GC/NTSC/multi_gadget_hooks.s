.memaddr 0x800e8f04
# Disable supercharge cost check in GadgetPad::Update
cmpwi 3, 0

.memaddr 0x800e81d4
# Disable supercharge cost check in GadgetPad::InitialiseStart
cmpwi 3, 0

.memaddr 0x800e8628
# Disable supercharge cost check in GadgetPad::CheckForLightGemChange
cmpwi 3, 0

.memaddr 0x800e8f5c
# Disable invincibility cost check GadgetPad::Update
cmpwi 3, 0

.memaddr 0x800e8260
# Disable invincibility cost check in GadgetPad::InitialiseStart
cmpwi 3, 0

.memaddr 0x800e86c8
# Disable invincibility cost check in GadgetPad::CheckForLightGemChange
cmpwi 3, 0

.memaddr 0x800e8e38
# Spoof ball gadget cost check in GadgetPad::Update
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook

.memaddr 0x800e87f8
# Spoof ball gadget cost check in GadgetPad::InitBallGadgetPad
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook

.memaddr 0x800e857c
# Spoof ball gadget cost check in GadgetPad::CheckForLightGemChange
bl GadgetPad__BallGadget__TotalLightGems_PreCallHook
