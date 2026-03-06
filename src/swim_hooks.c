#include <swim_hooks.h>
#include <player.h>
#include <gamestate.h>

Bool swim_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_SWIM) == 0) {
        return false;
    }

    return XSEItemHandler_Player__ButtonDown(self, button);
}

Bool swim_XSEItemHandler_Player__ButtonPressed_PreCallHook(void *self, Buttons button)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_SWIM) == 0) {
        return false;
    }

    return XSEItemHandler_Player__ButtonPressed(self, button);
}

void swim_XSEItemHandler_Player__SetMode_PreCallHook(void *self, PlayerModes mode, int force, int params)
{
    bool has_swim = (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_SWIM) != 0;
    if (!has_swim && (mode == water_dive)) {
        XSEItemHandler_Player__SetMode(self, water_paddle, force, params);
    } else {
        XSEItemHandler_Player__SetMode(self, mode, force, params);
    }
}
