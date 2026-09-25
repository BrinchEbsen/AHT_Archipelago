#include <BASIC_hooks.h>

GameScriptPatch const_gamescript_patches[] = {
    // Patch out a check that makes Hunter disappear if you do levels out of order.
    // If you visit Crocovile Swamp before meeting him, he'll disappear and won't
    // open the gate.
    {
        .trig_index = 10,
        .map_index = 24,
        .num_lines = 1,
        .patches = (GameScriptPatchLine[])
        {
            {
                .line_num = 0,
                // Original:    loc0 = GETOBJECTIVE HT_Objective_1B_Visited
                // Patched:     loc0 = 0
                .line_patch = { 0x0e1c0001, 0x00000000 }
            }
        }
    },
    // Make Ember not force a conversation when you meet her for the first time.
    // Otherwise you can horn dive the dark gem and start a conversation with her
    // at the same time, which can potentially soft lock the game.
    {
        .trig_index = 289,
        .map_index = 24,
        .num_lines = 1,
        .patches = (GameScriptPatchLine[])
        {
            {
                .line_num = 34,
                // Original:    FORCETALK
                // Patched:     glo0 = 0
                .line_patch = { 0x0e180001, 0x00000000 }
            }
        }
    }
};
