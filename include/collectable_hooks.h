#ifndef COLLECTABLE_HOOKS_H
#define COLLECTABLE_HOOKS_H
#include <types.h>
#include <trigger.h>
#include <gamestate.h>

#define XSEITEMHANDLER_ITEM_TRIGGER(self) OFFSET_VAL(SE_Trigger*, self, 0x10)

void LightXtal__Collected(void* this, Bool Register);
void LightXtal__Collected_VtableHook(void* this, Bool Register);

void DragonEgg__Collected(void* this, Bool Register);
void DragonEgg__Collected_VtableHook(void* this, Bool Register);

void DarkXtal__Collected(void* this, Bool Register);
void DarkXtal__Collected_VtableHook(void* this, Bool Register);

void LockedChest__OpenLockedChest(void* self);
void LockedChest__OpenLockedChest_PreCallHook(void* self);

#define EGGTHIEF_M_FLAGS(self) OFFSET_VAL(u32, self, 0x3dc)
#define EGGTHIEF_M_SITEM(self) OFFSET_VAL(void*, self, 0x518)
#define SPECIALITEM_M_STATUS(self) OFFSET_VAL(u32, self, 0x3e0)

s32 EggThief__EggCollection_ReImplHook(void* self);

void register_collectable(void* special_item);

extern void MemCard_AutoSave(void);

s32 PlayerState__AddDarkGems_ReImplHook(PlayerState* self, int n, SE_Map* pMap);
s32 PlayerState__AddDragonEggs_ReImplHook(PlayerState* self, int n, int Type, SE_Map* pMap);
s32 PlayerState__AddLightGems_ReImplHook(PlayerState* self, int n, SE_Map* pMap);

#endif /* COLLECTABLE_HOOKS_H */