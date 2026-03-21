#include <playerstate.h>
#include <ap_settings.h>

void PlayerState__IncLockPickers_ReImplHook(PlayerState* self, s8 lockpicks)
{
    // If shop is randomized
    if (g_gamestate_ap_settings.xls_shop_rowcount > 0) {
        return;
    }

    self->m_LockPickers += lockpicks;
    if (self->m_LockPickers > self->m_LockPickers_Max) {
        self->m_LockPickers = self->m_LockPickers_Max;
    }
}