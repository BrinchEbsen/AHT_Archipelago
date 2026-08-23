#include <charge_hooks.h>
#include <player.h>
#include <gamestate.h>
#include <hashcodes.h>

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

Bool paddle_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button)
{
    // If you can't charge underwater, we map the charge button to paddling.
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_CHARGE) == 0) {
        return  XSEItemHandler_Player__ButtonDown(self, but_charge) |
                XSEItemHandler_Player__ButtonDown(self, but_jump);
    }

    return XSEItemHandler_Player__ButtonDown(self, button);
}

bool charge_XSEItemHandler_PlayerCheckModeChange_PreCallHook(void* self, u32 NewAnimMode)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_CHARGE) == 0) {
        return XSEItemHandler_Player__CheckModeChange(self, HT_AnimMode_Swim_Run);
    }

    return XSEItemHandler_Player__CheckModeChange(self, NewAnimMode);
}
