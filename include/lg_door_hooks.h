#ifndef LG_DOOR_HOOKS_H
#define LG_DOOR_HOOKS_H
#include <types.h>

#define SWITCH_LIGHTGEM_M_COUNT(self) OFFSET_VAL(int, self, 0x458)

extern void Switch_LightGem__GetTriggerConfig(void* self);
void Switch_LightGem__GetTriggerConfig_VtableHook(void* self);

#endif /* LG_DOOR_HOOKS_H */