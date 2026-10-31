#ifndef CANNON_HOOKS_H
#define CANNON_HOOKS_H
#include <types.h>
#include <player.h>

#define XSEITEMHANDLER_CANNON_TALKINDICATORID(self) OFFSET_VAL(u32, self, 0x44c)
#define XSEITEMHANDLER_CANNON_INUSE(self) OFFSET_VAL(Bool, self, 0x450)

Bool cannon_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button);

void* cannon_EXItemHandler__ctor_PreCallHook(void* self);

extern int XSEItemHandler_Cannon__Update(void* self);
extern void gSetTalkIndicatorVisibility(u32 id, Bool state);
int XSEItemHandler_Cannon__Update_VtableHook(void* self);

#endif /* CANNON_HOOKS_H */
