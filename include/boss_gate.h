#ifndef BOSS_GATE_H
#define BOSS_GATE_H
#include <types.h>

typedef struct BossGateEntry
{
    u16 map_index;
    u16 trigger_index;
    u16 dark_gem_cost;
    EXHashCode clear_objective;
} BossGateEntry;

#define BOSS_GATE_NUM_ENTRIES 4
extern BossGateEntry g_boss_gate_list[];

#define XSEITEMHANDLER_M_PBASIC(self) OFFSET_VAL(void*, self, 0x380)
extern void SpyroBASIC__Update(void* self);
extern void Monitor__BASICcmd_Stall(void* self);
extern void Monitor__BASICcmd_Suicide(void* self);
extern s32 Monitor__BASICcmd_GetDistanceToPlayer(void* self);
extern void Monitor__BASICcmd_Zoopoo(void* self, u32 value);

void Monitor__BASIC_Update_PreCallHook(void* self);

void monitor_process_boss_gate(void* self, u16 cost, EXHashCode clear_objective);

#endif /* BOSS_GATE_H */