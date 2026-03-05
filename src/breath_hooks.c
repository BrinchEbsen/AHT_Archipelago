#include <breath_hooks.h>
#include <playerstate.h>
#include <gamestate.h>
#include <ap_settings.h>
#include <player.h>
#include <pad.h>
#include <gameloop.h>
#include <sfx.h>
#include <Sound.h>

bool XSEItemHandler_Spyro__TestBreatheFire__ReImplHook(void* self, int set)
{
    u32 abiflg = gGameState.m_PlayerState.m_AbilityFlags;
    bool no_breaths_unlocked
        = (abiflg & (ABILITY_ELECTRIC_BREATH | ABILITY_WATER_BREATH | ABILITY_ICE_BREATH)) == 0;

    bool enable_flame = (gGameState.m_PlayerState.m_AbilityFlags | ABILITY_AP_FIREBREATH) != 0;

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
    BreathType curr_breath = gGameState.m_PlayerState.m_CurrentBreath;

    void* pbreath = XSEItemHandler_Spyro__GetCurrentBreath(self);

    SpyroBreath__TestShooting_func test_shooting_func
        = SPYROBREATH_VTABLE_TESTSHOOTING(pbreath);
        
    bool test_shooting = test_shooting_func(pbreath);
    if (test_shooting) {
        return false;
    }

    bool controls_locked = XSEItemHandler_Player__ControlsLocked(self);
    if (controls_locked) {
        return false;
    }

    bool switchto = false;

    bool has_fire = (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_FIREBREATH) != 0;
    if (g_pad_button_state(PAD_BUTTON_DPAD_LEFT) && has_fire) {
        curr_breath = fire;
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT)) {
            switchto = true;
        }
    }

    bool has_water = (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_WATER_BREATH) != 0;
    if (g_pad_button_state(PAD_BUTTON_DPAD_RIGHT) && has_water) {
        curr_breath = water;
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_RIGHT)) {
            switchto = true;
        }
    }

    bool has_ice = (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_ICE_BREATH) != 0;
    if (g_pad_button_state(PAD_BUTTON_DPAD_DOWN) && has_water) {
        curr_breath = ice;
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
            switchto = true;
        }
    }

    bool has_elec = (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_ELECTRIC_BREATH) != 0;
    if (g_pad_button_state(PAD_BUTTON_DPAD_UP) && has_elec) {
        curr_breath = elec;
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_UP)) {
            switchto = true;
        }
    }

    if (curr_breath == gGameState.m_PlayerState.m_CurrentBreath) {
        if (switchto) {
            GUI_Panel__ForcePanelOn(gGameLoop.m_pPanel, 4, 180.0f);
        }
        return false;
    } else {
        pbreath = XSEItemHandler_Spyro__GetCurrentBreath(self);
        SpyroBreath__ChangeTo_func changeto_func = SPYROBREATH_VTABLE_CHANGETO(pbreath);
        changeto_func(pbreath, 0);
        PlaySFX(HT_Sound_SFX_GEN_HUD_CHANGE_BREATH);
        gGameState.m_PlayerState.m_CurrentBreath = curr_breath;
        pbreath = XSEItemHandler_Spyro__GetCurrentBreath(self);
        changeto_func(pbreath, 1);
        return true;
    }
}
