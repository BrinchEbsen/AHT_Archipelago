.memaddr 0x80148be4
# CPU_Base::SpawnPickups
bl CPU_Base__CreatedChestPickup_PreCallHook

.memaddr 0x8014906c
# CPU_Base::ReCreatedAllPickups
bl CPU_Base__CreatedChestPickup_PreCallHook

.memaddr 0x80429c78
# LockedChest ReleaseMyGems virtual method
.long LockedChest__ReleaseMyGems_VtableHook
