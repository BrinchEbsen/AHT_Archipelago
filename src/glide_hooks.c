#include <glide_hooks.h>
#include <pad.h>
#include <gamestate.h>
#include <player.h>

Bool glide_XSEItemHandler_Player__ButtonDown_PreCallHook(void *self, Buttons button)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_GLIDE) == 0) {
        return false;
    }

    return XSEItemHandler_Player__ButtonDown(self, button);
}