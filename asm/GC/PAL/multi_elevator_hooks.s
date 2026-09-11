.memaddr 0x801eb4b8
# Elevator 2A to 2C
bl SXI_Path__MoveAlongPath_PreCallHook_2Ato2C

.memaddr 0x801eb558
# Elevator 2C to 2A
bl SXI_Path__MoveAlongPath_PreCallHook_2Cto2A

.memaddr 0x801ea008
# All other elevators
bl FlippingPlatform__HandleFlip_PreCallHook
