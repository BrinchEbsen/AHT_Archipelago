#include <gate_hooks.h>
#include <map.h>

GateID gates_to_force_open[] = {
    // Locked gate before first Zoe
    {
        .map_index = 24,
        .trig_index = 153
    },
    // Dragon Village shop door
    {
        .map_index = 24,
        .trig_index = 271
    },
    // Dragon Village shop door
    {
        .map_index = 24,
        .trig_index = 308
    },
};
#define NUM_GATES_TO_FORCE_OPEN 3

void ScriptedGate__v_Preserve_VtableHook(void* self)
{
    ScriptedGate__v_Preserve(self);

    if (gate_should_force_open(self)) {
        SCRIPTEDGATE_M_STATUS(self) = 3;
    }
}

bool gate_should_force_open(void *pgate)
{
    SE_Map* map = GetSpyroMap(0);
    SE_Trigger* trigger = OFFSET_VAL(SE_Trigger*, pgate, 0x10);

    for (int i = 0; i < NUM_GATES_TO_FORCE_OPEN; i++) {
        if ((map->m_MapListIndex == gates_to_force_open[i].map_index) &&
            (trigger->m_GeoTriggerIndex == gates_to_force_open[i].trig_index)) {
            
            return true;
        }
    }

    return false;
}
