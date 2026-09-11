.memaddr 0x
# Charge button press check in TestWaterDive.
bl swim_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x
# Charge button down check in HandleCharge.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleChargePunch.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleSuperCharge.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleWalk.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleJump.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleJumpLand.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleDoubleJump.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleBreathe.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleFall.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button down check in HandleFallLand.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# In HandleJumpCharge, set mode to water_paddle instead of water_dive.
bl swim_XSEItemHandler_Player__SetMode_PreCallHook

.memaddr 0x
# In HandleJumpSlam, set mode to water_paddle instead of water_dive.
bl swim_XSEItemHandler_Player__SetMode_PreCallHook
