#include <ap_trap.h>
#include <system.h>
#include <pad.h>

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
        }
        else if (g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT))
        {
            g_gamestate_ap_settings.trap = TrapType_ReversedControls+1;
        }
    }
    #endif

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

    for (int i = 0; i < TrapType_NUM; i++)
    {
        if (traps_states[i] != 0)
        {
            traps_update_funcs[i](&traps_states[i]);
        }
    }
}

void ap_trap_moneybags_spam_call_update(u8* state)
{
    *state = 0;
}

void ap_trap_reverse_controls_update(u8 *state)
{
    *state = 0;
}
