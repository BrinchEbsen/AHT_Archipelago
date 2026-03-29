#ifndef GADGET_HOOK_H
#define GADGET_HOOK_H
#include <types.h>

#define DRAW_GADGET_COST_TEXT_RANGE 5.0f

#define GADGETPAD_M_GADGETTYPE(self) OFFSET_VAL(s32, self, 0x438)

extern int GadgetPad__Update(void* self);
int GadgetPad__Update_VtableHook(void* self);

void test_gadgetpad_printcost(void* self);

#endif /* GADGET_HOOK_H */