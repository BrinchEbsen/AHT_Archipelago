#ifndef CHARGE_HOOKS_H
#define CHARGE_HOOKS_H
#include <types.h>
#include <player.h>

Bool charge_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button);
Bool charge_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button);

#endif /* CHARGE_HOOKS_H */