#ifndef COLLECTABLE_HOOKS_H
#define COLLECTABLE_HOOKS_H
#include <types.h>
#include <trigger.h>
#include <gamestate.h>
#include <exvector.h>
#include <runtimeclass.h>

extern void LightXtal__Collected(void* this, Bool Register);
void LightXtal__Collected_VtableHook(void* this, Bool Register);

extern void DragonEgg__Collected(void* this, Bool Register);
void DragonEgg__Collected_VtableHook(void* this, Bool Register);

extern void DarkXtal__Collected(void* this, Bool Register);
void DarkXtal__Collected_VtableHook(void* this, Bool Register);

extern void LockedChest__OpenLockedChest(void* self);
void LockedChest__OpenLockedChest_PreCallHook(void* self);

extern Bool FireWorks__UpdatePathPosRot(void* self, float Speed);
extern EXRuntimeClass R4ZFireWorks__classR4ZFireWorks;
Bool FireWorks__UpdatePathPosRot_PreCallHook(void* self, float Speed);

#define EGGTHIEF_M_FLAGS(self) OFFSET_VAL(u32, self, 0x3dc)
#define EGGTHIEF_M_SITEM(self) OFFSET_VAL(void*, self, 0x518)
#define SPECIALITEM_M_STATUS(self) OFFSET_VAL(u32, self, 0x3e0)

s32 EggThief__EggCollection_ReImplHook(void* self);

void register_collectable(void* special_item);

s32 PlayerState__AddDarkGems_ReImplHook(PlayerState* self, int n, SE_Map* pMap);
s32 PlayerState__AddDragonEggs_ReImplHook(PlayerState* self, int n, int Type, SE_Map* pMap);
s32 PlayerState__AddLightGems_ReImplHook(PlayerState* self, int n, SE_Map* pMap);

#define CPU_BASE_M_PICKUPHASH(self) OFFSET_VAL(EXHashCode, self, 0x4e8)

extern EXRuntimeClass classLockedChest;

extern Bool CPU_Base__CreatedChestPickup(void* self, s32 Index, EXVector* Pos, void* Data);

extern Bool BaseChest__ReleaseMyGems(void* self);
Bool LockedChest__ReleaseMyGems_VtableHook(void* self);

extern void LockedChest__IdleUpdate(void* self);
void LockedChest__IdleUpdate_VtableHook(void* self);

#endif /* COLLECTABLE_HOOKS_H */