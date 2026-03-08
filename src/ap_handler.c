#include <ap_handler.h>
#include <ap_settings.h>
#include <ap_patch.h>
#include <ap_notification.h>
#include <system.h>
#include <pad.h>
#include <gamestate.h>
#include <map.h>
#include <hashcodes.h>
#include <ap_collectables.h>
#include <paneldraw.h>
#include <igstdlib.h>

#define NUM_REALM_INTRO_OBJECTIVES 7
EXHashCode realm_intro_objectives[] = {
    HT_Objective_OpeningMovie,
    HT_Objective_SeenIntro_R1A,
    HT_Objective_SeenProfStartR2A,
    HT_Objective_SeenIntroR2A,
    HT_Objective_SeenProfStartR3A,
    HT_Objective_SeenIntroR3A,
    HT_Objective_ProfGoneToFindRed
};

#define AP_DEBUG_ENABLE_ABILITIES

void ap_update()
{
    // The savefile data is initialized by checking if a magic value isn't set.
    if (g_gamestate_ap_settings.init != AP_SETTINGS_INIT_MAGICVALUE) {
        ap_init_gamestate();
    }
}

void ap_draw(void* pWnd)
{
    ap_draw_notification(pWnd);
}

void ap_init_gamestate()
{
    memcpy(&g_gamestate_ap_settings, &g_patch_ap_settings, sizeof(APSettings));

    g_gamestate_ap_settings.init = AP_SETTINGS_INIT_MAGICVALUE;

    #ifdef AP_DEBUG_ENABLE_ABILITIES
    gGameState.m_PlayerState.m_AbilityFlags |= (
        ABILITY_AP_FIREBREATH |
        ABILITY_AP_GLIDE |
        ABILITY_AP_CHARGE |
        ABILITY_AP_SWIM
    );
    #endif

    if (g_patch_ap_settings.skip_realm_intro_cutscenes) {
        for (int i = 0; i < NUM_REALM_INTRO_OBJECTIVES; i++) {
            PlayerObjectives__SetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, realm_intro_objectives[i]);
        }
    }
}

void ap_set_grabbable(u16 map_index, u16 trigger_index)
{
    int index = ap_binary_search_grabbable(map_index, trigger_index);
    if (index < 0) {
        return;
    }

    ap_set_location(index);
}

void ap_set_objective(EXHashCode objective)
{
    for (int i = AP_OBJECTIVES_START; i < AP_OBJECTIVES_START+AP_OBJECTIVES_NUM; i++) {
        APCollectable* coll = &g_ap_collectables[i];
        if (coll->objective.objective == objective) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_location(int index)
{
    int byte = index / 8;
    int bit = index % 8;

    u8* val = &g_gamestate_ap_settings.location_bitfield[byte];

    if (((*val) & (1 << bit)) == 0) {
        (*val) |= (1 << bit);
        PRINTF("[AP] Set location flag index %d\n", index);
    }
}

int ap_binary_search_grabbable(u16 map_index, u16 trigger_index)
{
    int start = AP_GRABBABLE_START;
    int end = AP_GRABBABLE_START + AP_GRABBABLE_NUM - 1;

    while (start <= end) {
        int index = start + ((end-start)/2);
        APCollectable* curr = &g_ap_collectables[index];

        if ((map_index == curr->grabbable.map_index) &&
            (trigger_index == curr->grabbable.trigger_index)) {
            return index;
        }

        if ((map_index < curr->grabbable.map_index) ||
            ((map_index == curr->grabbable.map_index) &&
            (trigger_index < curr->grabbable.trigger_index))) {
            end = index - 1;
        } else {
            start = index + 1;
        }
    }

    return -1;
}

s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow *self)
{
    if (gp_paneldraw_loop == NULL) {
        GUI_Base* paneldraw = paneldraw_create();
        if (paneldraw != NULL) {
            paneldraw_callback = ap_draw;
        }
    }

    ap_update();

    return SEGameFlow__v_StateRunning(self);
}
