#ifndef BREATH_HOOK_H
#define BREATH_HOOK_H
#include <types.h>

extern void* XSEItemHandler_Spyro__GetCurrentBreath(void* this);

typedef bool(*SpyroBreath__TestBreathe_func)(void*, int);

#define SPYROBREATH_VTABLE_TESTBREATHE(self) \
    OFFSET_VAL(SpyroBreath__TestBreathe_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x18)

bool XSEItemHandler_Spyro__TestBreatheFire__ReImplHook(void* self, int set);

// NOT HOOKED YET
bool XSEItemHandler_Spyro__TestBreathChange__ReImplHook(void* self);

#endif /* BREATH_HOOK_H */