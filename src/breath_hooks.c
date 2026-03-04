#include <breath_hooks.h>
#include <playerstate.h>
#include <gamestate.h>
#include <ap_settings.h>

bool XSEItemHandler_Spyro__TestBreatheFire__ReImplHook(void* self, int set)
{
    u32 abiflg = gGameState.m_PlayerState.m_AbilityFlags;
    bool no_breaths_unlocked
        = (abiflg & (ABILITY_ELECTRIC_BREATH | ABILITY_WATER_BREATH | ABILITY_ICE_BREATH)) == 0;

    bool enable_flame = g_gamestate_ap_settings.firebreath_enable;

    if (no_breaths_unlocked && !enable_flame)
    {
        return false;
    }

    void* breath = XSEItemHandler_Spyro__GetCurrentBreath(self);

    SpyroBreath__TestBreathe_func func = SPYROBREATH_VTABLE_TESTBREATHE(breath);

    return func(breath, set);
}

bool XSEItemHandler_Spyro__TestBreathChange__ReImplHook(void *self)
{
    return false;
}
