.memaddr 0x
# Elevator 2A to 2C
bl SXI_Path__MoveAlongPath_PreCallHook_2Ato2C

.memaddr 0x
# Elevator 2C to 2A
bl SXI_Path__MoveAlongPath_PreCallHook_2Cto2A

.memaddr 0x
# All other elevators
bl FlippingPlatform__HandleFlip_PreCallHook
