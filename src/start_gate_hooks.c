#include <start_gate_hooks.h>
#include <map.h>

void ScriptedGate__v_Preserve_VtableHook(void* self)
{
    ScriptedGate__v_Preserve(self);

    SE_Map* map = GetSpyroMap(0);
    SE_Trigger* trigger = OFFSET_VAL(SE_Trigger*, self, 0x10);
    if ((map->m_MapListIndex == 24) && (trigger->m_GeoTriggerIndex == START_GATE_TRIGGER_INDEX)) {
        SCRIPTEDGATE_M_STATUS(self) = 3;
    }
}
