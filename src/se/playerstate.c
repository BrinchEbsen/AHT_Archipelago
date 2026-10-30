#include <playerstate.h>
#include <ap_settings.h>
#include <map.h>
#include <ap_keys.h>

void PlayerState__IncLockPickers_ReImplHook(PlayerState* self, s8 lockpicks)
{
    // If shop is randomized or we're using keyrings,
    // don't let the game increase the key count.
    if (AP_GAMESTATE_SHOP_IS_RANDOMIZED | (g_gamestate_ap_settings.key_mode == KeyMode_KeyRings)) {
        return;
    }

    // If we're using per-level lockpicks, we increment the level counts instead.
    if (g_gamestate_ap_settings.key_mode == KeyMode_PerLevelLockpicks)
    {
        SE_Map* map = GetSpyroMap(0);
        int index = ap_keys_get_level_index(map);
        if (index >= 0)
        {
            u8 count = g_gamestate_ap_settings.perlevel_lockpicks[index].num_total;
            u8 max = g_ap_keys_num_chests[index];
            if (count < max) {
                g_gamestate_ap_settings.perlevel_lockpicks[index].num++;
                g_gamestate_ap_settings.perlevel_lockpicks[index].num_total++;
            }
            return;
        }
    }

    self->m_LockPickers += lockpicks;
    if (self->m_LockPickers > self->m_LockPickers_Max) {
        self->m_LockPickers = self->m_LockPickers_Max;
    }
}