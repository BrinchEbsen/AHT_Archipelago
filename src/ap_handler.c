#include <ap_handler.h>
#include <ap_settings.h>
#include <ap_patch.h>
#include <system.h>
#include <pad.h>
#include <gamestate.h>
#include <map.h>
#include <hashcodes.h>
#include <ap_collectables.h>

//#define AP_DEBUG_ENABLE_ABILITIES

void ap_update()
{
    if (g_gamestate_ap_settings.init != AP_SETTINGS_INIT_MAGICVALUE) {
        ap_init_gamestate();
    }
}

void ap_init_gamestate()
{
    APSettings* from = &g_patch_ap_settings;
    APSettings* to = &g_gamestate_ap_settings;

    for (int i = 0; i < AP_SETTINGS_LOCATIONS_BITFIELD_SIZE; i++) {
        to->location_bitfield[i] = from->location_bitfield[i];
    }
    to->starting_breath = from->starting_breath;
    to->starting_abilities = from->starting_abilities;
    #ifdef AP_DEBUG_ENABLE_ABILITIES
    gGameState.m_PlayerState.m_AbilityFlags |= (
        ABILITY_AP_FIREBREATH |
        ABILITY_AP_GLIDE |
        ABILITY_AP_CHARGE |
        ABILITY_AP_SWIM
    );
    #endif
    to->free_realm_travel_enable = from->free_realm_travel_enable;
    to->skip_realm_intro_cutscenes = from->skip_realm_intro_cutscenes;

    if (from->skip_realm_intro_cutscenes) {
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_OpeningMovie);
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_SeenIntro_R1A);
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_SeenProfStartR2A);
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_SeenIntroR2A);
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_SeenProfStartR3A);
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_SeenIntroR3A);
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_ProfGoneToFindRed);
    }

    g_gamestate_ap_settings.init = AP_SETTINGS_INIT_MAGICVALUE;
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

void print_trigger_array_code()
{
    SE_Map* map = GetSpyroMap(0);
    if (map == NULL) {
        return;
    }

    SE_TriggerList* list = &map->m_TriggerList;
    if (list->m_pTriggers == NULL) {
        return;
    }

    for (int i = 0; i < list->m_NumTriggers; i++) {
        SE_Trigger* trigger = list->m_pTriggers[i].m_pSE_Trigger;

        char* typestr = NULL;
        switch (trigger->m_TypeHashCode) {
            case HT_TriggerType_LightXtal: {
                typestr = "            .type = LightGem\n";
            } break;
            case HT_TriggerType_DragonEgg: {
                typestr = "            .type = DragonEgg\n";
            } break;
            case HT_TriggerType_DarkXtal: {
                typestr = "            .type = DarkGem\n";
            } break;
            case HT_TriggerType_Chest_Locked: {
                switch (trigger->m_EXTrigger.m_Data[0].h) {
                    case HT_ChestCreate_LightGem:
                        typestr = "            .type = LightGem_Chest\n";
                        break;
                    case HT_ChestCreate_DragonEgg2:
                    case HT_ChestCreate_DragonEgg3:
                    case HT_ChestCreate_DragonEgg4:
                    case HT_ChestCreate_DragonEgg5:
                    case HT_ChestCreate_DragonEgg6:
                    case HT_ChestCreate_DragonEgg7:
                    case HT_ChestCreate_DragonEgg8:
                        typestr = "            .type = DragonEgg_Chest\n";
                        break;
                }
            } break;
            case HT_TriggerType_EggThief: {
                typestr = "            .type = EggThief\n";
            } break;
        }

        if (typestr == NULL) {
            continue;
        }

        PRINTF("    {\n");
        PRINTF("        .union_type = APC_Grabbable,\n");
        PRINTF("        .grabbable = {\n");
        PRINTF("            .map_index = %d,\n", map->m_MapListIndex);
        PRINTF("            .trigger_index = %d,\n", i);
        PRINTF(typestr);
        PRINTF("        }\n");
        PRINTF("    },\n");
    }
}
