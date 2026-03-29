#include <gadget_hooks.h>
#include <trigger.h>
#include <player.h>
#include <exvector.h>
#include <ap_handler.h>
#include <ap_settings.h>
#include <hashcodes.h>

int GadgetPad__Update_VtableHook(void* self)
{
    test_gadgetpad_printcost(self);

    return GadgetPad__Update(self);
}

void test_gadgetpad_printcost(void* self)
{
    if (gpPlayerItem == NULL) {
        return;
    }

    s32 unlocked;
    int cost;
    switch (GADGETPAD_M_GADGETTYPE(self)) {
        case 2:
            PlayerObjectives__GetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, HT_Objective_SuperchargePowered, &unlocked);
            cost = g_gamestate_ap_settings.supercharge_cost;
            break;
        case 3:
            PlayerObjectives__GetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, HT_Objective_InvincibilityPowered, &unlocked);
            cost = g_gamestate_ap_settings.invincibility_cost;
            break;
        default:
            return;
    }

    // Don't draw text if unlocked
    if (unlocked != 0) {
        return;
    }

    SE_Trigger* trigger = OFFSET_VAL(SE_Trigger*, self, 0x10);

    EXVector3* triggerpos = &trigger->m_Position;
    EXVector* playerpos = OFFSET_PTR(EXVector, gpPlayerItem, 0xD0);

    float dist = EXVector_Dist((EXVector*)triggerpos, playerpos);
    if (dist < DRAW_GADGET_COST_TEXT_RANGE) {
        draw_cost_text = true;
        cost_text_type = COST_LightGem;
        cost_text_amt = cost;
    }
}
