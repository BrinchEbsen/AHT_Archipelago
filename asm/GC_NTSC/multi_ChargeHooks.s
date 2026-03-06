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
