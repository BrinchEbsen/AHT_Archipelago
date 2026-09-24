#ifndef NPC_HOOKS_H
#define NPC_HOOKS_H
#include <types.h>

extern int XSEItemHandler_NPC__InitNPC(void* self);
int XSEItemHandler_NPC__InitNPC_PreCallHook(void* self);

#endif /* NPC_HOOKS_H */