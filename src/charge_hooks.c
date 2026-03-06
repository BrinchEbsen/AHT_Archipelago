#include <charge_hooks.h>
#include <player.h>
#include <gamestate.h>

Bool charge_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_CHARGE) == 0) {
        return false;
    }

    return XSEItemHandler_Player__ButtonDown(self, button);
}

Bool charge_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_CHARGE) == 0) {
        return false;
    }

    return XSEItemHandler_Player__ButtonPressed(self, button);
}
