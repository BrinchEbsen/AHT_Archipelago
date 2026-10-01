#include <ap_collectables.h>
#include <ap_settings.h>
#include <hashcodes.h>
#include <system.h>
#include <util.h>

void ap_set_grabbable(u16 map_index, u16 trigger_index)
{
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->objective != 0xFFFF) {
			// This is an objective
            continue;
        }

        if ((coll->map_index == map_index) &&
            (coll->trig_index == trigger_index)) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_objective(EXHashCode objective)
{
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->objective == 0xFFFF) {
			// This is a grabbable
            continue;
        }

        if (coll->objective == (objective & 0xFFFF)) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_location(int index)
{
    if (!set_u8_bitfield_value(g_gamestate_ap_settings.location_bitfield, index*2, true)) {
        PRINTF("[AP] Set location flag index %d\n", index);
    }
}

s32 num_collectables_in_map(u16 map_index, s32* out_num_collected, s32* out_num_reachable)
{
    s32 num = 0;
    *out_num_collected = 0;
    *out_num_reachable = 0;

    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->map_index != map_index)
        {
            continue;
        }

        num++;

        size_t byte = (i*2) / 8;
        size_t bit = (i*2) % 8;
        u8 dat = g_gamestate_ap_settings.location_bitfield[byte];

        if ((dat & (0b01 << bit)) != 0) {
            (*out_num_collected)++;
        }
        if ((dat & (0b10 << bit)) != 0) {
            (*out_num_reachable)++;
        }
    }

    return num;
}

bool get_minigame_collectable_config(APCollectable* coll, bool* out_easyonly, bool* out_disabled)
{
    switch (coll->minigame_type)
    {
        case MinigameType_Blink:
            *out_easyonly = g_gamestate_ap_settings.minigame_blink_config == MinigameConfig_EasyOnly;
            *out_disabled = g_gamestate_ap_settings.minigame_blink_config == MinigameConfig_Disabled;
            return true;
        case MinigameType_Sparx:
            *out_easyonly = g_gamestate_ap_settings.minigame_sparx_config == MinigameConfig_EasyOnly;
            *out_disabled = g_gamestate_ap_settings.minigame_sparx_config == MinigameConfig_Disabled;
            return true;
        case MinigameType_Turret:
            *out_easyonly = g_gamestate_ap_settings.minigame_turret_config == MinigameConfig_EasyOnly;
            *out_disabled = g_gamestate_ap_settings.minigame_turret_config == MinigameConfig_Disabled;
            return true;
        case MinigameType_SgtByrd:
            *out_easyonly = g_gamestate_ap_settings.minigame_sgtbyrd_config == MinigameConfig_EasyOnly;
            *out_disabled = g_gamestate_ap_settings.minigame_sgtbyrd_config == MinigameConfig_Disabled;
            return true;
        default:
            *out_easyonly = false;
            *out_disabled = false;
            return false;
    }
}
