#include <gamestate.h>
#include <hashcodes.h>
#include <ap_handler.h>
#include <ap_settings.h>

bool g_sync_objectives_and_abilities = true;

void PlayerObjectives__SetObjective__ReImplHook(PlayerObjectives* self, EXHashCode hashcode)
{
    ap_set_objective(hashcode);

    int o_index;
    int o_bit;
    bool isValidHash = PlayerObjectives__ObjectiveIntoIndexAndBit(self, hashcode, &o_index, &o_bit);

    if (!isValidHash) {
        return;
    }

    if (o_index > 15) {
        while (true) { /* infinite loop */ }
    }

    uint* uintVal = &self->m_CompletedObjectives[o_index];
    uint mask = 1 << o_bit;
    bool objSet = ((*uintVal) & mask) != 0;
    
    if (objSet) {
        return;
    }

    *uintVal |= mask;

    // Setting the ability flags was part of the original function, but it
    // has been decoupled from objectives.

    // switch (hashcode) {
    //     case HT_Objective_GainedLockPicker:
    //         gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_BOUGHT_LOCK_PICK;
    //         break;
    //     case HT_Objective_GivenDoubleJump:
    //         gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_DOUBLE_JUMP;
    //         break;
    //     case HT_Objective_GivenPoleGrabAbility:
    //         gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_POLE_SPIN;
    //         break;
    //     case HT_Objective_GivenWallKickAbility:
    //         gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_WALL_KICK;
    //         break;
    //     case HT_Objective_GivenWingShieldAbility:
    //         gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_WING_SHIELD;
    //         break;
    // }
}
