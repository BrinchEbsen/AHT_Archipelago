#include <collectable_hooks.h>

void LightXtal__Collected_VtableHook(void *this, Bool Register)
{
    LightXtal__Collected(this, Register);
}

void DragonEgg__Collected_VtableHook(void *this, Bool Register)
{
    DragonEgg__Collected(this, Register);
}

void DarkXtal__Collected_VtableHook(void *this, Bool Register)
{
    DarkXtal__Collected(this, Register);
}
