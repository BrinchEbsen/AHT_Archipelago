#ifndef COLLECTABLE_HOOKS_H
#define COLLECTABLE_HOOKS_H
#include <types.h>

void LightXtal__Collected(void* this, Bool Register);
void LightXtal__Collected_VtableHook(void* this, Bool Register);

void DragonEgg__Collected(void* this, Bool Register);
void DragonEgg__Collected_VtableHook(void* this, Bool Register);

void DarkXtal__Collected(void* this, Bool Register);
void DarkXtal__Collected_VtableHook(void* this, Bool Register);

#endif /* COLLECTABLE_HOOKS_H */