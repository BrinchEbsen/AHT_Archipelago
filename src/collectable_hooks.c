#include <collectable_hooks.h>
#include <ap_collectables.h>
#include <ap_settings.h>
#include <map.h>

void LightXtal__Collected_VtableHook(void *this, Bool Register)
{
    register_collectable(this);
    LightXtal__Collected(this, Register);
}

void DragonEgg__Collected_VtableHook(void *this, Bool Register)
{
    register_collectable(this);
    DragonEgg__Collected(this, Register);
}

void DarkXtal__Collected_VtableHook(void *this, Bool Register)
{
    register_collectable(this);

    DarkXtal__Collected(this, Register);
}

void register_collectable(void* special_item)
{
    SE_Trigger* trigger = XSEITEMHANDLER_ITEM_TRIGGER(special_item);
    if (trigger == NULL) {
        return;
    }

    SE_Map* map = GetSpyroMap(0);
    if (map == NULL) {
        return;
    }

    int index = binary_search_for_collectable(map->m_MapListIndex, trigger->m_GeoTriggerIndex);
    if (index < 0) {
        return;
    }

    ap_set_collectable(index);
}

int binary_search_for_collectable(u16 map_index, u16 trigger_index)
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

s32 PlayerState__AddDarkGems_ReImplHook(PlayerState *self, int n, SE_Map *pMap)
{
    if (pMap == NULL) {
        pMap = GetSpyroMap(0);
        if (pMap == NULL) {
            return -1;
        }
    }

    int* curr_count = &pMap->m_GameState->m_CollectNum[0];
    (*curr_count) += n;

    // this is where adding the total count would be done. not in archipelago

    PlayerState__Update(self);
    MemCard_AutoSave();

    return *curr_count;
}

s32 PlayerState__AddDragonEggs_ReImplHook(PlayerState *self, int n, int Type, SE_Map *pMap)
{
    int _type = Type;
    if (_type == -1) {
        _type = 2;
    }
    
    if (pMap == NULL) {
        pMap = GetSpyroMap(0);
        if (pMap == NULL) {
            return -1;
        }
    }

    s32 num = SE_Map__GetNumDragonEggs(pMap, _type);
    SE_Map__SetNumDragonEggs(pMap, num+n, _type);
    num = SE_Map__GetNumDragonEggs(pMap, _type);

    // this is where adding the total count would be done. not in archipelago

    PlayerState__Update(self);
    MemCard_AutoSave();

    return num;
}

s32 PlayerState__AddLightGems_ReImplHook(PlayerState *self, int n, SE_Map *pMap)
{
    if (pMap == NULL) {
        pMap = GetSpyroMap(0);
        if (pMap == NULL) {
            return -1;
        }
    }

    int* curr_count = &pMap->m_GameState->m_CollectNum[1];
    (*curr_count) += n;

    // this is where adding the total count would be done. not in archipelago

    PlayerState__Update(self);
    MemCard_AutoSave();

    return *curr_count;
}
