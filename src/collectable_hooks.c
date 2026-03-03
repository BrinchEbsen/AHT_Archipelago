#include <collectable_hooks.h>
#include <ap_collectables.h>
#include <ap_settings.h>
#include <ap_handler.h>
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

void LockedChest__OpenLockedChest_PreCallHook(void* self)
{
    register_collectable(self);

    LockedChest__OpenLockedChest(self);
}

s32 EggThief__EggCollection_ReImplHook(void* self)
{
    void* sItem = EGGTHIEF_M_SITEM(self);

    if (sItem == NULL) {
        return 2;
    }

    u32 sItemStatus = SPECIALITEM_M_STATUS(sItem);
    if (sItemStatus > 5) {
        EGGTHIEF_M_SITEM(self) = NULL;
        EGGTHIEF_M_FLAGS(self) |= 8;

        register_collectable(self);

        return -1;
    }

    return 2;
}

void register_collectable(void* handler)
{
    SE_Trigger* trigger = XSEITEMHANDLER_ITEM_TRIGGER(handler);
    if (trigger == NULL) {
        return;
    }

    SE_Map* map = GetSpyroMap(0);
    if (map == NULL) {
        return;
    }

    ap_set_grabbable(map->m_MapListIndex, trigger->m_GeoTriggerIndex);
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
