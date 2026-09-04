#include <ap_trap.h>
#include <system.h>
#include <pad.h>
#include <player.h>
#include <gameloop.h>
#include <sfx.h>
#include <Sound.h>
#include <exrand.h>
#include <exitemenv.h>

/*
 * Each trap is given an "update" function with a state.
 * A state of 0 is non-running, a state of 1 is "starting" or "waiting", and
 * any state after that means different stages of the routine.
 * A trap stops itself by setting the state to 0.
 */

u8 traps_states[TrapType_NUM] = {0};

ap_trap_update_func traps_update_funcs[TrapType_NUM] =
{
    [TrapType_MoneyBagsSpamCall]    = ap_trap_moneybags_spam_call_update,
    [TrapType_ReversedControls]     = ap_trap_reverse_controls_update
};

void ap_trap_update()
{
    #if AP_DEBUG_TRAPS!=0
    if (g_pad_button_state(PAD_BUTTON_B))
    {
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN))
        {
            g_gamestate_ap_settings.trap = TrapType_MoneyBagsSpamCall+1;
            g_gamestate_ap_settings.trap_data = 60*60;
        }
        else if (g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT))
        {
            g_gamestate_ap_settings.trap = TrapType_ReversedControls+1;
            g_gamestate_ap_settings.trap_data = 60*60;
        }
    }
    #endif

    // If a trap has been requested, set the appropriate trap's state to 1.
    if (g_gamestate_ap_settings.trap != 0)
    {
        // Client sets this trap field to a non-zero value.
        // The type is derived from this field minus 1.
        u8 type = g_gamestate_ap_settings.trap-1;
        if (type < TrapType_NUM)
        {
            traps_states[type] = 1;
        }
        g_gamestate_ap_settings.trap = 0;
    }

    // Update any traps that are running.
    for (int i = 0; i < TrapType_NUM; i++)
    {
        if (traps_states[i] != 0)
        {
            traps_update_funcs[i](&traps_states[i]);
        }
    }
}

u16 mb_voicelines_hashes[] =
{
    HT_Sound_SPEECH_MBG_006 & 0xFFFF,
    HT_Sound_SPEECH_MBG_007 & 0xFFFF,
    HT_Sound_SPEECH_MBG_008 & 0xFFFF,
    HT_Sound_SPEECH_MBG_009 & 0xFFFF,
    HT_Sound_SPEECH_MBG_010 & 0xFFFF,
    HT_Sound_SPEECH_MBG_011 & 0xFFFF,
    HT_Sound_SPEECH_MBG_012 & 0xFFFF,
    HT_Sound_SPEECH_MBG_014 & 0xFFFF,
    HT_Sound_SPEECH_MBG_015 & 0xFFFF,
    HT_Sound_SPEECH_MBG_017 & 0xFFFF,
    HT_Sound_SPEECH_MBG_018 & 0xFFFF,
    HT_Sound_SPEECH_MBG_030 & 0xFFFF,
    HT_Sound_SPEECH_MBG_033 & 0xFFFF,
    HT_Sound_SPEECH_MBG_035 & 0xFFFF,
    HT_Sound_SPEECH_MBG_036 & 0xFFFF,
    HT_Sound_SPEECH_MBG_037 & 0xFFFF,
    HT_Sound_SPEECH_MBG_039 & 0xFFFF,
    HT_Sound_SPEECH_MBG_040 & 0xFFFF,
    HT_Sound_SPEECH_MBG_042 & 0xFFFF,
    HT_Sound_SPEECH_MBG_043 & 0xFFFF
};

void ap_trap_moneybags_spam_call_update(u8* state)
{
    static s32 timer = 0;

    if (gpPlayer == NULL)
    {
        return;
    }

    if (gGameLoop.m_GameIsPaused || (gGameLoop.m_State != Running))
    {
        return;
    }

    switch (*state)
    {
        case 1:
            timer = g_gamestate_ap_settings.trap_data;
            int line_index = RAND32 % ARRAY_SIZE(mb_voicelines_hashes);
            PlaySFX(0x1AF00000 | mb_voicelines_hashes[line_index]);
            XSEItemEnv__StartMusic_ReImplHook(EXItemEnv__m_pTheItemEnv, HT_Sound_MFX_Shop, 0, 0, 0);
            lock_music_to_shop = true;
            *state = 2;
            return;
        case 2:
        default:
            timer--;
            if (timer <= 0)
            {
                lock_music_to_shop = false;
                *state = 0;
            }
            return;
    }
}

void ap_trap_reverse_controls_update(u8* state)
{
    static s32 timer = 0;

    switch (*state)
    {
        case 1:
            timer = g_gamestate_ap_settings.trap_data;
            pad_reverse_analog = true;
            *state = 2;
            return;
        case 2:
        default:
            timer--;
            if (timer <= 0)
            {
                pad_reverse_analog = false;
                *state = 0;
            }
            return;
    }
}
