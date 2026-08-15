#ifndef CHARGE_HOOKS_H
#define CHARGE_HOOKS_H
#include <types.h>
#include <player.h>

// A bunch of hooks into button handling functions, made to return false if
// the flag for the ability isn't set. Calls are replaced with a multi-patch.

Bool charge_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button);
Bool charge_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button);

#endif /* CHARGE_HOOKS_H */