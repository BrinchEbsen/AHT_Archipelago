#include <trigger_hooks.h>
#include <system.h>
#include <map.h>

void SE_TriggerList__ConstructAll_PreCallHook(SE_TriggerList* self)
{
    // Grab the map data and check if it's Dark Mine.
    // If it is, apply a fix to adjust a loading trigger.
    void* map_anim = self->m_pMap->m_pMapAnimator;
    if (map_anim != NULL)
    {
        void* geo_map = EXItemAnimator_Map__GetGeoMap(map_anim);
        if (geo_map != NULL)
        {
            if (self->m_pMap->m_MapListIndex == 30) // dark mine
            {
                correct_dark_mine_loading_trigger(geo_map);
            }
        }
    }

    SE_TriggerList__ConstructAll(self);
}

void correct_dark_mine_loading_trigger(void* p_geo_map)
{
    // Pointer math is funky because of the way the data is formatted with relative pointers

    s32 trigger_header_offset = OFFSET_VAL(s32, p_geo_map, 0x58);
    void* trigger_header = OFFSET_PTR(void, p_geo_map, 0x58 + trigger_header_offset);

    s32 triggers_offset = OFFSET_VAL(s32, trigger_header, 0x4);
    s32* p_triggers = OFFSET_PTR(s32, trigger_header, 0x4 + triggers_offset);

    s32 loadtrigger_offset = p_triggers[217*2];
    EXGeoTrigger* p_trigger = OFFSET_PTR(EXGeoTrigger, &p_triggers[217*2], loadtrigger_offset);

    p_trigger->Rotation.y = 2.215784f;
}
