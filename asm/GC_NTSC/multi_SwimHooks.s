.memaddr 0x8008c6d4
# Charge button press check in TestWaterDive.
bl swim_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x800a1788
# Charge button down check in HandleCharge.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a2478
# Charge button down check in HandleChargePunch.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a1e70
# Charge button down check in HandleSuperCharge.
bl swim_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800ab0bc
# In HandleJumpCharge, set mode to water_paddle instead of water_dive.
bl swim_XSEItemHandler_Player__SetMode_PreCallHook

.memaddr 0x800a9ba4
# In HandleJumpSlam, set mode to water_paddle instead of water_dive.
bl swim_XSEItemHandler_Player__SetMode_PreCallHook
