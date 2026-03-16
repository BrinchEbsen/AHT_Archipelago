#include <lg_door_hooks.h>
#include <trigger.h>
#include <map.h>
#include <ap_settings.h>

void Switch_LightGem__GetTriggerConfig_VtableHook(void* self)
{
    Switch_LightGem__GetTriggerConfig(self);

    SE_Trigger* pTrigger = OFFSET_VAL(SE_Trigger*, self, 0x10);
    SE_Map* pMap = (SE_Map*)pTrigger->m_pMap;

    if (pMap == NULL) return;

    switch (pMap->m_RealmID)
    {
        case Realm_1:
            SWITCH_LIGHTGEM_M_COUNT(self) = g_gamestate_ap_settings.lg_door_costs[0];
            break;
        case Realm_2:
            SWITCH_LIGHTGEM_M_COUNT(self) = g_gamestate_ap_settings.lg_door_costs[1];
            break;
        case Realm_3:
            SWITCH_LIGHTGEM_M_COUNT(self) = g_gamestate_ap_settings.lg_door_costs[2];
            break;
        case Realm_4:
            SWITCH_LIGHTGEM_M_COUNT(self) = g_gamestate_ap_settings.lg_door_costs[3];
            break;
    }
}
