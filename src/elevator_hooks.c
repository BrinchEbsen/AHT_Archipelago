#include <elevator_hooks.h>
#include <ap_settings.h>
#include <gamestate.h>

void teleport_to_elevator_endpoint(int map_index, EXHashCode startpoint)
{
    SE_Map* goto_map = gMapList.m_List[map_index].m_pMap;
    goto_map->m_GameState->m_LastStartPoint = startpoint;
    gGameState.m_StartMapIndex = map_index;
    PlayerState__RestartGame(&gGameState.m_PlayerState);
}

void SXI_Path__MoveAlongPath_PreCallHook_2Ato2C(void* self, float DeltaDist, Bool UseSpline)
{
    if (g_gamestate_ap_settings.instant_elevators) {
        teleport_to_elevator_endpoint(ELEVATOR_2A_2C_MAPINDEX, ELEVATOR_2A_2C_STARTPOINT);
    }
    
    SXI_Path__MoveAlongPath(self, DeltaDist, UseSpline);
}

void SXI_Path__MoveAlongPath_PreCallHook_2Cto2A(void* self, float DeltaDist, Bool UseSpline)
{
    if (g_gamestate_ap_settings.instant_elevators) {
        teleport_to_elevator_endpoint(ELEVATOR_2C_2A_MAPINDEX, ELEVATOR_2C_2A_STARTPOINT);
    }
    
    SXI_Path__MoveAlongPath(self, DeltaDist, UseSpline);
}

void test_elevator_teleport(void* elevator)
{
    SE_Trigger* trigger = OFFSET_VAL(SE_Trigger*, elevator, 0x10);
    if (trigger == NULL) return;

    SE_Map* map = trigger->m_pMap;
    if (map == NULL) return;

    s16 ti = trigger->m_GeoTriggerIndex;
    s32 mi = map->m_MapListIndex;

    int map_index;
    EXHashCode startpoint;
    if ((ti == ELEVATOR_SUNKENRUINS_TRIGGERINDEX) && (mi == ELEVATOR_SUNKENRUINS_MAPINDEX))
    {
        SE_Map* currmap = GetSpyroMap(0);
        if (currmap == NULL) return;

        if (currmap->m_MapGeoHashCode == HT_File_Realm2A) {
            map_index  = ELEVATOR_2A_2B_MAPINDEX;
            startpoint = ELEVATOR_2A_2B_STARTPOINT;
        } else if (currmap->m_MapGeoHashCode == HT_File_Realm2B) {
            map_index  = ELEVATOR_2B_2A_MAPINDEX;
            startpoint = ELEVATOR_2B_2A_STARTPOINT;
        }
        else { return; }
    }
    else if ((ti == ELEVATOR_MAGMAFALLS_TRIGGERINDEX) && (mi == ELEVATOR_MAGMAFALLS_MAPINDEX))
    {
        SE_Map* currmap = GetSpyroMap(0);
        if (currmap == NULL) return;

        if (currmap->m_MapGeoHashCode == HT_File_Realm4B) {
            map_index  = ELEVATOR_4B_4C_MAPINDEX;
            startpoint = ELEVATOR_4B_4C_STARTPOINT;
        } else if (currmap->m_MapGeoHashCode == HT_File_Realm4C) {
            map_index  = ELEVATOR_4C_4B_MAPINDEX;
            startpoint = ELEVATOR_4C_4B_STARTPOINT;
        }
        else { return; }
    }
    else { return; }

    teleport_to_elevator_endpoint(map_index, startpoint);
}

void FlippingPlatform__HandleFlip_PreCallHook(void* self)
{
    if (g_gamestate_ap_settings.instant_elevators) {
        test_elevator_teleport(self);
    }
    
    FlippingPlatform__HandleFlip(self);
}