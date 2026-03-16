#ifndef BASIC_HOOKS_H
#define BASIC_HOOKS_H
#include <types.h>

typedef struct BossGateEntry
{
    u16 map_index;
    u16 trigger_index;
    EXHashCode clear_objective;
} BossGateEntry;

#define BOSS_GATE_NUM_ENTRIES 4
extern BossGateEntry g_boss_gate_list[];

typedef struct GameScriptPatch
{
    u16 trig_index;
    u16 map_index;
    int num_lines;
    int start_line;
    u32* patches;
} GameScriptPatch;

#define NUM_GAMESCRIPT_PATCHES 1
extern GameScriptPatch g_gamescript_patches[];

#define XSEITEMHANDLER_M_PBASIC(self) OFFSET_VAL(void*, self, 0x380)

#define SPYROBASIC_SCRIPTCODE(self) OFFSET_VAL(u32*, self, 0x18)

#define BASICMAIN_OWNER(self) OFFSET_VAL(void*, self, 0x28)

extern void SpyroBASIC__Update(void* self);
extern bool SpyroBASIC__Init(void* self, void* owner);
extern bool BASIC_Main__Init(void* self, void* owner);
extern u32 BASIC_Main__RunScript(void* self, s32 num);
bool BASIC_Main__UpdatePointers(void* self);
extern void Monitor__BASICcmd_Stall(void* self);
extern void Monitor__BASICcmd_Suicide(void* self);
extern s32 Monitor__BASICcmd_GetDistanceToPlayer(void* self);
extern void Monitor__BASICcmd_Zoopoo(void* self, u32 value);

void XSEItemHandler_Base__BASIC_Update_ReImplHook(void* self);

void monitor_process_boss_gate(void* self, int index);

bool BASIC_Main__UpdatePointers_PreCallHook(void* self);

void apply_gamescript_patch(void* self, GameScriptPatch* patch);

#endif /* BASIC_HOOKS_H */