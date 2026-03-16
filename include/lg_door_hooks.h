#ifndef LG_DOOR_HOOKS_H
#define LG_DOOR_HOOKS_H
#include <types.h>

#define DRAW_LG_COST_TEXT_RANGE 15.0f

#define SWITCH_LIGHTGEM_M_COUNT(self) OFFSET_VAL(int, self, 0x458)

extern void Switch_LightGem__GetTriggerConfig(void* self);
void Switch_LightGem__GetTriggerConfig_VtableHook(void* self);

extern int Switch_LightGem__Update(void* self);
int Switch_LightGem__Update_VtableHook(void* self);

void test_draw_lg_count(void* self);

u8 get_lg_count(void* self);

#endif /* LG_DOOR_HOOKS_H */