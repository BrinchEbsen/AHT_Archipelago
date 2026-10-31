#include <cannon_hooks.h>
#include <gamestate.h>
#include <exitemenv.h>

Bool cannon_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button)
{
    if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_CANNON) == 0) {
        return false;
    }

    return XSEItemHandler_Player__ButtonPressed(self, button);
}

void* cannon_EXItemHandler__ctor_PreCallHook(void* self)
{
    void* ret = EXItemHandler__EXItemHandler(self);

    // Annoyingly, the "in use" variable isn't initialized on this object's
    // creation, so we hook into the constructor to initialize it ourselves.
    XSEITEMHANDLER_CANNON_INUSE(self) = false;

    return ret;
}

int XSEItemHandler_Cannon__Update_VtableHook(void* self)
{
    // Make talk indicator visible only if the ability flag is set (and not in use).
    if (!XSEITEMHANDLER_CANNON_INUSE(self))
    {
        gSetTalkIndicatorVisibility(
            XSEITEMHANDLER_CANNON_TALKINDICATORID(self),
            (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_AP_CANNON) != 0
        );
    }

    return XSEItemHandler_Cannon__Update(self);
}
