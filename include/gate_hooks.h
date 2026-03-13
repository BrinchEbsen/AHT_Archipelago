#ifndef GATE_HOOKS_H
#define GATE_HOOKS_H
#include <types.h>

#define SCRIPTEDGATE_M_STATUS(self) OFFSET_VAL(u32, self, 0x3E0)
#define START_GATE_TRIGGER_INDEX 153
#define START_GATE_MAP 24

typedef struct GateID
{
    u16 trig_index;
    u16 map_index;
} GateID;

extern GateID gates_to_force_open[];

extern void ScriptedGate__v_Preserve(void* self);

void ScriptedGate__v_Preserve_VtableHook(void* self);

bool gate_should_force_open(void* pgate);

#endif /* GATE_HOOKS_H */