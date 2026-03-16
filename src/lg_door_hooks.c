#include <lg_door_hooks.h>
#include <trigger.h>
#include <map.h>
#include <ap_settings.h>
#include <ap_handler.h>
#include <player.h>
#include <exvector.h>

void Switch_LightGem__GetTriggerConfig_VtableHook(void* self)
{
    Switch_LightGem__GetTriggerConfig(self);

    u8 count = get_lg_count(self);
    if (count > 0) {
        SWITCH_LIGHTGEM_M_COUNT(self) = count;
    }
}

int Switch_LightGem__Update_VtableHook(void* self)
{
    test_draw_lg_count(self);

    return Switch_LightGem__Update(self);
}

void test_draw_lg_count(void* self)
{
    if (gpPlayerItem == NULL) return;

    EXVector* playerPos = OFFSET_PTR(EXVector, gpPlayerItem, 0xD0);
    EXVector* switchPos = OFFSET_PTR(EXVector, OFFSET_VAL(void*, self, 0), 0xD0);

    float dist = EXVector_Dist(playerPos, switchPos);
    
    if (dist > DRAW_LG_COST_TEXT_RANGE) {
        return;
    }

    u8 count = get_lg_count(self);
    if (count > 0) {
        draw_cost_text = true;
        cost_text_type = COST_LightGem;
        cost_text_amt = count;
    }
}

u8 get_lg_count(void *self)
{
    SE_Trigger* pTrigger = OFFSET_VAL(SE_Trigger*, self, 0x10);
    SE_Map* pMap = (SE_Map*)pTrigger->m_pMap;

    if (pMap == NULL) return 0;

    switch (pMap->m_RealmID)
    {
        case Realm_1:
            return g_gamestate_ap_settings.lg_door_costs[0];
            break;
        case Realm_2:
            return g_gamestate_ap_settings.lg_door_costs[1];
            break;
        case Realm_3:
            return g_gamestate_ap_settings.lg_door_costs[2];
            break;
        case Realm_4:
            return g_gamestate_ap_settings.lg_door_costs[3];
            break;
    }

    return 0;
}
