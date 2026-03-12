#ifndef BREATH_HOOK_H
#define BREATH_HOOK_H
#include <types.h>

extern void* XSEItemHandler_Spyro__GetCurrentBreath(void* this);

typedef bool(*SpyroBreath__TestShooting_func)(void*);
#define SPYROBREATH_VTABLE_TESTSHOOTING(self) \
    OFFSET_VAL(SpyroBreath__TestShooting_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x10)

typedef bool(*SpyroBreath__TestSecondaryShot_func)(void*, int);
#define SPYROBREATH_VTABLE_TESTSECONDARYSHOT(self) \
    OFFSET_VAL(SpyroBreath__TestSecondaryShot_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x14)

typedef bool(*SpyroBreath__TestBreathe_func)(void*, int);
#define SPYROBREATH_VTABLE_TESTBREATHE(self) \
    OFFSET_VAL(SpyroBreath__TestBreathe_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x18)

typedef bool(*SpyroBreath__ChangeTo_func)(void*, int);
#define SPYROBREATH_VTABLE_CHANGETO(self) \
    OFFSET_VAL(SpyroBreath__ChangeTo_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x1c)

extern void GUI_Panel__ForcePanelOn(void* self, int section, float time);

bool XSEItemHandler_Spyro__TestBreatheFire__ReImplHook(void* self, int set);

bool XSEItemHandler_Spyro__TestShooter__ReImplHook(void* self, int set);

bool XSEItemHandler_Spyro__TestBreathChange__ReImplHook(void* self);

#endif /* BREATH_HOOK_H */