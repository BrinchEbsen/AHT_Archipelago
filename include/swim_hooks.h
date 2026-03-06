#ifndef SWIM_HOOKS_H
#define SWIM_HOOKS_H
#include <types.h>
#include <player.h>

Bool swim_XSEItemHandler_Player__ButtonDown_PreCallHook(void* self, Buttons button);
Bool swim_XSEItemHandler_Player__ButtonPressed_PreCallHook(void* self, Buttons button);
void swim_XSEItemHandler_Player__SetMode_PreCallHook(void* self, PlayerModes mode, int force, int params);

#endif /* SWIM_HOOKS_H */