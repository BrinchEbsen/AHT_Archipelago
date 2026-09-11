.memaddr 0x8008c778
# Charge button press check in TestWaterDive.
bl swim_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x800a182c
# Charge button down check in HandleCharge.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a251c
# Charge button down check in HandleChargePunch.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a1f14
# Charge button down check in HandleSuperCharge.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800ac4e8
# Charge button down check in HandleWalk.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a8498
# Charge button down check in HandleJump.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a8848
# Charge button down check in HandleJumpLand.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a904c
# Charge button down check in HandleDoubleJump.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a4ed8
# Charge button down check in HandleBreathe.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a2c8c
# Charge button down check in HandleFall.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a3078
# Charge button down check in HandleFallLand.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800ab18c
# In HandleJumpCharge, set mode to water_paddle instead of water_dive.
bl swim_XSEItemHandler_Player__SetMode_PreCallHook

.memaddr 0x800a9c74
# In HandleJumpSlam, set mode to water_paddle instead of water_dive.
bl swim_XSEItemHandler_Player__SetMode_PreCallHook
