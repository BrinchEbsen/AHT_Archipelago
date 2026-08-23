.memaddr 0x800a0e14
# Charge button press check in TestChargePunch.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x800a0e2c
# Charge button hold check in TestChargePunch.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a0dc0
# Charge button press check in TestCharge.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x800a0dd8
# Charge button hold check in TestCharge.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a6cac
# Charge button press check in TestJumpCharge.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x8008f50c
# Charge button press check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x8008f5c4
# Charge button press check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonPressed_PreCallHook

.memaddr 0x8008f788
# Charge button hold check in HandleWaterDive.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008f520
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008f79c
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008f5ec
# Jump button hold check in HandleWaterDive (make charge button also paddle).
bl paddle_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x8008e8bc
# Animmode change in TestWaterDive (make diving underwater use paddle animmode).
bl charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook

.memaddr 0x8008f240
# Animmode change in TestWaterDive (make diving underwater use paddle animmode).
bl charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook

.memaddr 0x8008fcf8
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800901f4
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x80090234
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800902d4
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x80090310
# Charge button hold check in HandleWaterSurface.
bl charge_XSEItemHandler_Player__ButtonDown_PreCallHook
