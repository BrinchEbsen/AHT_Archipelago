.memaddr 0x801eae58
# Elevator 2A to 2C
bl SXI_Path__MoveAlongPath_PreCallHook_2Ato2C

.memaddr 0x801eaef8
# Elevator 2C to 2A
bl SXI_Path__MoveAlongPath_PreCallHook_2Cto2A

.memaddr 0x801e99a8
# All other elevators
bl FlippingPlatform__HandleFlip_PreCallHook
