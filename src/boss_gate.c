#include <boss_gate.h>
#include <trigger.h>
#include <map.h>
#include <gamestate.h>
#include <hashcodes.h>

BossGateEntry g_boss_gate_list[] = {
    // Gnasty Gnorc
    {
        .map_index = 24,
        .trigger_index = 349,
        .dark_gem_cost = 10,
        .clear_objective = HT_Objective_RA_RemovedBossBarrier
    },
    // Ineptune
    {
        .map_index = 45,
        .trigger_index = 236,
        .dark_gem_cost = 20,
        .clear_objective = HT_Objective_RB_RemovedBossBarrier
    },
    // Red
    {
        .map_index = 31,
        .trigger_index = 319,
        .dark_gem_cost = 30,
        .clear_objective = HT_Objective_RC_RemovedBossBarrier
    },
    // Mecha Red
    {
        .map_index = 40,
        .trigger_index = 394,
        .dark_gem_cost = 40,
        .clear_objective = HT_Objective_RD_RemovedBossBarrier
    }
};

void Monitor__BASIC_Update_PreCallHook(void* self)
{
    SE_Map* pMap = GetSpyroMap(0);
    if (pMap != NULL) {
        SE_Trigger* pTrigger = XSEITEMHANDLER_ITEM_TRIGGER(self);

        if (pTrigger != NULL) {
            for (int i = 0; i < BOSS_GATE_NUM_ENTRIES; i++) {
                BossGateEntry* entry = &g_boss_gate_list[i];

                // Check if this is a boss gate monitor trigger
                if ((entry->map_index == pMap->m_MapListIndex) &&
                    (entry->trigger_index == pTrigger->m_GeoTriggerIndex))
                {
                    monitor_process_boss_gate(self, entry->dark_gem_cost, entry->clear_objective);
                    return;
                }
            }
        }
    }

    void* pBasic = XSEITEMHANDLER_M_PBASIC(self);
    if (pBasic != NULL) {
        SpyroBASIC__Update(pBasic);
    }
}

void monitor_process_boss_gate(void* self, u16 cost, EXHashCode clear_objective)
{
    s32 obj;
    PlayerObjectives__GetObjective(
        &gGameState.m_PlayerObjectives, clear_objective, &obj);

    // Kill trigger if barrier already gone
    if (obj != 0) {
        Monitor__BASICcmd_Suicide(self);
        return;
    }

    // Wait until enough dark gems
    int numDarkGem = gGameState.m_PlayerState.m_TotalDarkGems;
    if (numDarkGem < cost) {
        return;
    }

    // Wait until player is in range
    int dist = Monitor__BASICcmd_GetDistanceToPlayer(self);
    if (dist > 1500) {
        return;
    }

    // Start script to remove barrier
    Monitor__BASICcmd_Zoopoo(self, HT_ScriptEvents_SetLight);
    // Clear boss barrier objective
    PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, clear_objective);
    // Kill trigger
    Monitor__BASICcmd_Suicide(self);
}
