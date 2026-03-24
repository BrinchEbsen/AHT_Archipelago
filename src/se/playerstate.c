#include <playerstate.h>
#include <ap_settings.h>

void PlayerState__IncLockPickers_ReImplHook(PlayerState* self, s8 lockpicks)
{
    // If shop is randomized or we're using keyrings,
    // don't let the game increase the key count.
    if (AP_GAMESTATE_SHOP_IS_RANDOMIZED | AP_GAMESTATE_USE_KEY_RINGS) {
        return;
    }

    self->m_LockPickers += lockpicks;
    if (self->m_LockPickers > self->m_LockPickers_Max) {
        self->m_LockPickers = self->m_LockPickers_Max;
    }
}