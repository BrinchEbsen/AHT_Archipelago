.memaddr 0x800a0e14
# Charge button press check in TestChargePunch.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x800a0ed0
# Charge button hold check in TestChargePunch.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a0e64
# Charge button press check in TestCharge.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x800a0e7c
# Charge button hold check in TestCharge.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a6d7c
# Charge button press check in TestJumpCharge.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x8008f5b0
# Charge button press check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x8008f668
# Charge button press check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x8008f82c
# Charge button hold check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008f5c4
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008f840
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008f690
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008e960
# Animmode change in HandleWaterDive (make diving underwater use paddle animmode).
bl charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook

.memaddr 0x8008f2e4
# Animmode change in HandleWaterDive (make diving underwater use paddle animmode).
bl charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook

.memaddr 0x8008fd9c
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x80090298
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800902d8
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x80090378
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800903b4
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook
