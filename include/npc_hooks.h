#ifndef NPC_HOOKS_H
#define NPC_HOOKS_H
#include <types.h>
#include <gamestate.h>

extern int XSEItemHandler_NPC__InitNPC(void* self);
int XSEItemHandler_NPC__InitNPC_PreCallHook(void* self);

bool minigame_onloaded_PlayerObjectives__GetObjective_PreCallHook(PlayerObjectives* self, EXHashCode hashcode, s32* result);

#endif /* NPC_HOOKS_H */