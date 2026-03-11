#ifndef START_GATE_HOOKS_H
#define START_GATE_HOOKS_H
#include <types.h>

#define SCRIPTEDGATE_M_STATUS(self) OFFSET_VAL(u32, self, 0x3E0)
#define START_GATE_TRIGGER_INDEX 153
#define START_GATE_MAP 24

extern void ScriptedGate__v_Preserve(void* self);

void ScriptedGate__v_Preserve_VtableHook(void* self);

#endif /* START_GATE_HOOKS_H */