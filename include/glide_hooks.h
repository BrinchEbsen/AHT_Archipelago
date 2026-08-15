#ifndef GLIDE_HOOKS_H
#define GLIDE_HOOKS_H
#include <types.h>
#include <player.h>

// A hook into a button handling function, made to return false if the flag
// for the ability isn't set. Calls are replaced with a multi-patch.

Bool glide_XSEItemHandler_Player__ButtonDown_PreCallHook(void *self, Buttons button);

#endif /* GLIDE_HOOKS_H */