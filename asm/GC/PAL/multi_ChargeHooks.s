.memaddr 0x
# Charge button press check in TestChargePunch.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x
# Charge button hold check in TestChargePunch.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button press check in TestCharge.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x
# Charge button hold check in TestCharge.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button press check in TestJumpCharge.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x
# Charge button press check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x
# Charge button press check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x
# Charge button hold check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Animmode change in TestWaterDive (make diving underwater use paddle animmode).
bl charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook

.memaddr 0x
# Animmode change in TestWaterDive (make diving underwater use paddle animmode).
bl charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook

.memaddr 0x
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook
