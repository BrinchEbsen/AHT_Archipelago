.memaddr 0x800e8f04
# Disable supercharge cost check
cmpwi 3, 0

.memaddr 0x800e8f5c
# Disable invincibility cost check
cmpwi 3, 0

.memaddr 0x800e8e38
# Spoof ball gadget cost check
bl GadgetPad__Update__TotalLightGems_PreCallHook
