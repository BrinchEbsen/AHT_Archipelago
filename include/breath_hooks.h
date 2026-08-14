#ifndef BREATH_HOOK_H
#define BREATH_HOOK_H
#include <types.h>

extern void* XSEItemHandler_Spyro__GetCurrentBreath(void* this);

typedef bool(*SpyroBreath__TestShooting_func)(void*);
// Get the "TestShooting" virtual function
#define SPYROBREATH_VTABLE_TESTSHOOTING(self) \
    OFFSET_VAL(SpyroBreath__TestShooting_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x10)

typedef bool(*SpyroBreath__TestSecondaryShot_func)(void*, int);
// Get the "TestSecondaryShot" virtual function
#define SPYROBREATH_VTABLE_TESTSECONDARYSHOT(self) \
    OFFSET_VAL(SpyroBreath__TestSecondaryShot_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x14)

typedef bool(*SpyroBreath__TestBreathe_func)(void*, int);
// Get the "TestBreathe" virtual function
#define SPYROBREATH_VTABLE_TESTBREATHE(self) \
    OFFSET_VAL(SpyroBreath__TestBreathe_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x18)

typedef bool(*SpyroBreath__ChangeTo_func)(void*, int);
// Get the "ChangeTo" virtual function
#define SPYROBREATH_VTABLE_CHANGETO(self) \
    OFFSET_VAL(SpyroBreath__ChangeTo_func, \
        OFFSET_VAL(void*, self, 0x34), \
        0x1c)

extern void GUI_Panel__ForcePanelOn(void* self, int section, float time);

// Re-implementation of TestBreatheFire to adjust for fire breath being a toggleable ability.
bool XSEItemHandler_Spyro__TestBreatheFire__ReImplHook(void* self, int set);

// Re-implementation of TestShooter to adjust for fire breath being a toggleable ability.
bool XSEItemHandler_Spyro__TestShooter__ReImplHook(void* self, int set);

// Re-implementation of TestBreathChange to adjust for fire breath being a toggleable ability.
bool XSEItemHandler_Spyro__TestBreathChange__ReImplHook(void* self);

#define ELECBREATH_M_FLAGS(self) OFFSET_VAL(int, self, 0x80)
#define ELECBREATH_M_GALPHATARGET(self) OFFSET_VAL(float, self, 0xA4)
#define ELECBREATH_M_SFX(self) OFFSET_VAL(int, self, 0x14c)

extern Bool EXSoundTag__IsPlaying(void* self);
extern void ElecBreath__PlaySound(void* self, Bool onoff);

// Re-implementation of ElecBreath::Stop to fix a crashing bug in the vanilla game.
void ElecBreath__Stop_ReImplHook(void* self);

#endif /* BREATH_HOOK_H */