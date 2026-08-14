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
// A list of boss gate triggers and their associated objectives for clearing them.
extern BossGateEntry g_boss_gate_list[];

// A patch for a gamescript.
typedef struct GameScriptPatch
{
    // The trigger containing the gamescript.
    u16 trig_index;
    // The map containing the trigger.
    u16 map_index;
    // Number of script lines to patch.
    u16 num_lines;
    // The starting line to patch from.
    u16 start_line;
    // Pointer to the values to patch into the gamescript.
    u32* patches;
} GameScriptPatch;

#define NUM_GAMESCRIPT_PATCHES 2
// Array of gamescript patches.
extern GameScriptPatch g_gamescript_patches[];

#define XSEITEMHANDLER_M_PBASIC(self) OFFSET_VAL(void*, self, 0x380)

#define SPYROBASIC_SCRIPTCODE(self) OFFSET_VAL(u32*, self, 0x18)

#define BASICMAIN_OWNER(self) OFFSET_VAL(void*, self, 0x28)

#define DRAW_DG_COST_TEXT_RANGE 1500

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

// A function that replaces the gamescript for boss gates.
void monitor_process_boss_gate(void* self, int index);

// Draw dark gem cost text if the player is close enough.
void test_draw_boss_gate_cost(void* self, int index);

bool BASIC_Main__UpdatePointers_PreCallHook(void* self);

void apply_gamescript_patch(void* self, GameScriptPatch* patch);

// Make every item believe supercharge and invincibility is active so the
// professor never shows up to explain it
Bool XSEItemHandler_Base__BASICcmd_GetObjective_ReImplHook(void* self, u32 hashcode, s32 *result);

#endif /* BASIC_HOOKS_H */