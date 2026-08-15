#ifndef SWIM_HOOKS_H
#define SWIM_HOOKS_H
#include <types.h>
#include <player.h>

// A bunch of hooks into button handling functions, made to return false if
// the flag for the ability isn't set. Calls are replaced with a multi-patch.

Bool swim_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button);
Bool swim_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button);

// A hook into SetMode, to force the mode to be water_paddle if it tries setting
// the mode to water_dive without the swim ability's flag being set.
void swim_XSEItemHandler_Player__SetMode_PreCallHook(void* self, PlayerModes mode, int force, int params);

#endif /* SWIM_HOOKS_H */