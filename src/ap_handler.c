#include <ap_handler.h>
#include <system.h>
#include <pad.h>
#include <gamestate.h>
#include <map.h>
#include <hashcodes.h>
#include <ap_collectables.h>

void ap_update()
{
    if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
        print_trigger_array_code();
    }
}

void update_objectives(EXHashCode objective)
{
    
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
