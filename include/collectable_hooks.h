#ifndef COLLECTABLE_HOOKS_H
#define COLLECTABLE_HOOKS_H
#include <types.h>
#include <trigger.h>

#define XSEITEMHANDLER_ITEM_TRIGGER(self) OFFSET_VAL(SE_Trigger*, self, 0x10)

void LightXtal__Collected(void* this, Bool Register);
void LightXtal__Collected_VtableHook(void* this, Bool Register);

void DragonEgg__Collected(void* this, Bool Register);
void DragonEgg__Collected_VtableHook(void* this, Bool Register);

void DarkXtal__Collected(void* this, Bool Register);
void DarkXtal__Collected_VtableHook(void* this, Bool Register);

void register_collectable(void* special_item);

int binary_search_for_collectable(u16 map_index, u16 trigger_index);

#endif /* COLLECTABLE_HOOKS_H */