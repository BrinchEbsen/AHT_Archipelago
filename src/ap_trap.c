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

s32 traps_params[TrapType_NUM] = {0};

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
            traps_params[type] = g_gamestate_ap_settings.trap_data;
        }
        g_gamestate_ap_settings.trap = 0;
        g_gamestate_ap_settings.trap_data = 0;
    }

    // Update any traps that are running.
    for (int i = 0; i < TrapType_NUM; i++)
    {
        if (traps_states[i] != 0)
        {
            traps_update_funcs[i](&traps_states[i], &traps_params[i]);
        }
    }
}

MBTrapEntry mb_voicelines[] = { //               Time in frames = Time (ms) * 1000/60
    { .sfx_hash = HT_Sound_SPEECH_MBG_006 & 0xFFFF, .time = (u16)(3195u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_007 & 0xFFFF, .time = (u16)(5732u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_008 & 0xFFFF, .time = (u16)(1905u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_009 & 0xFFFF, .time = (u16)(2303u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_010 & 0xFFFF, .time = (u16)(2926u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_011 & 0xFFFF, .time = (u16)(1671u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_012 & 0xFFFF, .time = (u16)(5176u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_014 & 0xFFFF, .time = (u16)(3020u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_015 & 0xFFFF, .time = (u16)(3578u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_017 & 0xFFFF, .time = (u16)(4422u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_018 & 0xFFFF, .time = (u16)(4190u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_030 & 0xFFFF, .time = (u16)(10392u    * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_033 & 0xFFFF, .time = (u16)(6943u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_035 & 0xFFFF, .time = (u16)(3413u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_036 & 0xFFFF, .time = (u16)(3187u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_037 & 0xFFFF, .time = (u16)(3680u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_039 & 0xFFFF, .time = (u16)(2936u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_040 & 0xFFFF, .time = (u16)(5003u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_042 & 0xFFFF, .time = (u16)(2453u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
    { .sfx_hash = HT_Sound_SPEECH_MBG_043 & 0xFFFF, .time = (u16)(2738u     * 0.06f) + SPAM_CALL_TRAP_VOICELINE_COOLDOWN },
};

void ap_trap_moneybags_spam_call_update(u8* state, s32* param)
{
    static int voice_timer = 0;
    static int line_index_last = 0;

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
            // Lock to shop music
            XSEItemEnv__StartMusic_ReImplHook(EXItemEnv__m_pTheItemEnv, HT_Sound_MFX_Shop, 0, 0, 0);
            lock_music_to_shop = true;
            voice_timer = 0;
            *state = 2;
            return;
        case 2:
        default:
            if (voice_timer <= 0)
            {
                // Choose random voice line.
                // Try not to play the same line twice.
                int line_index;
                do {
                    line_index = RAND32 % ARRAY_SIZE(mb_voicelines);
                } while (line_index == line_index_last);
                line_index_last = line_index;

                // Play the voice line and set the timer to its length.
                PlaySFX(0x1AF00000 | mb_voicelines[line_index].sfx_hash);
                voice_timer = mb_voicelines[line_index].time;
            }
            voice_timer--;

            (*param)--;
            if (*param <= 0)
            {
                lock_music_to_shop = false;
                *state = 0;
            }
            return;
    }
}

void ap_trap_reverse_controls_update(u8* state, s32* param)
{
    switch (*state)
    {
        case 1:
            pad_reverse_analog = true;
            *state = 2;
            return;
        case 2:
        default:
            (*param)--;
            if (*param <= 0)
            {
                pad_reverse_analog = false;
                *state = 0;
            }
            return;
    }
}
