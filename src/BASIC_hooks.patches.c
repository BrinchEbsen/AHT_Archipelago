#include <BASIC_hooks.h>

#pragma region Const Patches
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
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1c, 0)
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
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x18, 0)
            }
        }
    }
};
#pragma endregion

#pragma region Reusables
GameScriptPatchLine reusable_patch_1[] = {
    // Make NPC never think the light gem challenge is completed.
    {
        .line_num = 4,
        // Original:    glo3 = GETOBJECTIVE <minigame hard complete objective>
        // Patched:     glo3 = 0
        .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1b, 0)
    },
    // Make NPC not ask about the light gem challenge.
    {
        .line_num = 79,
        // Original:    CALLPROC PlayCutsc_6
        // Patched:     glo2 = 1
        .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1a, 1)
    },
    // Prevent the yes/no box to choose the light gem from appearing.
    {
        .line_num = 93,
        // Original:    YESNOBOX HT_Text_ASK_GEM
        // Patched:     YESNO = 0
        .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x5, 0)
    }
};
GameScriptPatchLine reusable_patch_2[] = {
    // Make NPC never think the light gem challenge is completed.
    {
        .line_num = 7,
        // Original:    glo5 = GETOBJECTIVE <minigame hard complete objective>
        // Patched:     glo5 = 0
        .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1d, 0)
    },
    // Prevent the yes/no box to choose the light gem from appearing.
    {
        .line_num = 91,
        // Original:    glo12 = HT_Text_ASK_GEM
        // Patched:     CALLPROC play
        .line_patch = BASIC_HOOK_CALL_PROC(0x2)
    },
    {
        .line_num = 92,
        // Original:    CALLPROC play
        // Patched:     TALKCAMERA 0
        .line_patch = BASIC_HOOK_TALK_CAMERA(0)
    },
    {
        .line_num = 93,
        // Original:    CALLPROC quiz
        // Patched:     TALKTOPLAYER 0
        .line_patch = BASIC_HOOK_TALK_TO_PLAYER(0)
    },
    {
        .line_num = 103,
        // Original:    glo12 = HT_Text_ASK_GEM
        // Patched:     TALKCAMERA 0
        .line_patch = BASIC_HOOK_TALK_CAMERA(0)
    },
    {
        .line_num = 104,
        // Original:    CALLPROC quiz
        // Patched:     TALKTOPLAYER 0
        .line_patch = BASIC_HOOK_TALK_TO_PLAYER(0)
    }
};
#pragma endregion

#pragma region Blink Easy Only
GameScriptPatch blink_easyonly_patches[] = {
    // Crocovile Swamp Blink
    {
        .trig_index = 69,
        .map_index = 23,
        .num_lines = 3,
        .patches = (GameScriptPatchLine[])
        {
            // Make NPC never think the light gem challenge is completed.
            {
                .line_num = 4,
                // Original:    glo3 = GETOBJECTIVE <minigame hard complete objective>
                // Patched:     glo3 = 0
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1b, 0)
            },
            // Make NPC not ask about the light gem challenge.
            {
                .line_num = 88,
                // Original:    CALLPROC PlayCutsc_6
                // Patched:     glo2 = 1
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1a, 1)
            },
            // Prevent the yes/no box to choose the light gem from appearing.
            {
                .line_num = 102,
                // Original:    YESNOBOX HT_Text_ASK_GEM
                // Patched:     YESNO = 0
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x5, 0)
            }
        }
    },
    // Coastal Remains Blink
    {
        .trig_index = 115,
        .map_index = 45,
        .num_lines = 7,
        .patches = (GameScriptPatchLine[])
        {
            // Make NPC never think the light gem challenge is completed.
            {
                .line_num = 7,
                // Original:    glo5 = GETOBJECTIVE <minigame hard complete objective>
                // Patched:     glo5 = 0
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1d, 0)
            },
            // Prevent the yes/no box to choose the light gem from appearing.
            {
                .line_num = 91,
                // Original:    glo12 = HT_Text_ASK_GEM
                // Patched:     CALLPROC play
                .line_patch = BASIC_HOOK_CALL_PROC(0x2)
            },
            {
                .line_num = 92,
                // Original:    CALLPROC play
                // Patched:     TALKCAMERA 0
                .line_patch = BASIC_HOOK_TALK_CAMERA(0)
            },
            {
                .line_num = 93,
                // Original:    CALLPROC quiz
                // Patched:     TALKTOPLAYER 0
                .line_patch = BASIC_HOOK_TALK_TO_PLAYER(0)
            },
            {
                .line_num = 97,
                // Original:    glo12 = HT_Text_ASK_GEM
                // Patched:     glo7 = 1
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1f, 1)
            },
            {
                .line_num = 103,
                // Original:    glo7 = 1
                // Patched:     TALKCAMERA 0
                .line_patch = BASIC_HOOK_TALK_CAMERA(0)
            },
            {
                .line_num = 104,
                // Original:    CALLPROC quiz
                // Patched:     TALKTOPLAYER 0
                .line_patch = BASIC_HOOK_TALK_TO_PLAYER(0)
            }
        }
    },
    // Frostbite Village Blink
    {
        .trig_index = 244,
        .map_index = 31,
        .num_lines = 3,
        .patches = reusable_patch_1
    },
    // Dark Mine Blink
    {
        .trig_index = 154,
        .map_index = 30,
        .num_lines = 6,
        .patches = reusable_patch_2
    }
};
#pragma endregion

#pragma region Sparx Easy Only
GameScriptPatch sparx_easyonly_patches[] = {
    // Dragonfly Falls Sparx
    {
        .trig_index = 0,
        .map_index = 22,
        .num_lines = 0,
        .patches = NULL
    },
    // Sunken Ruins Sparx
    {
        .trig_index = 0,
        .map_index = 19,
        .num_lines = 0,
        .patches = NULL
    },
    // Gloomy Glacier Sparx
    {
        .trig_index = 0,
        .map_index = 35,
        .num_lines = 0,
        .patches = NULL
    },
    // Magma Falls Bottom Sparx
    {
        .trig_index = 0,
        .map_index = 63,
        .num_lines = 0,
        .patches = NULL
    }
};
#pragma endregion

#pragma region Turret Easy Only
GameScriptPatch turret_easyonly_patches[] = {
    // Crocovile Swamp Turret
    {
        .trig_index = 0,
        .map_index = 23,
        .num_lines = 0,
        .patches = NULL
    },
    // Coastal Remains Turret
    {
        .trig_index = 0,
        .map_index = 45,
        .num_lines = 0,
        .patches = NULL
    },
    // Frostbite Village Turret
    {
        .trig_index = 0,
        .map_index = 31,
        .num_lines = 0,
        .patches = NULL
    },
    // Stormy Beach Turret
    {
        .trig_index = 0,
        .map_index = 44,
        .num_lines = 0,
        .patches = NULL
    }
};
#pragma endregion

#pragma region Sgt. Byrd Easy Only
GameScriptPatch sgtbyrd_easyonly_patches[] = {
    // Dragon Village Sgt. Byrd
    {
        .trig_index = 158,
        .map_index = 24,
        .num_lines = 3,
        .patches = reusable_patch_1
    },
    // Cloudy Domain Sgt. Byrd
    {
        .trig_index = 81,
        .map_index = 20,
        .num_lines = 6,
        .patches = (GameScriptPatchLine[])
        {
            // Make NPC never think the light gem challenge is completed.
            {
                .line_num = 7,
                // Original:    glo5 = GETOBJECTIVE <minigame hard complete objective>
                // Patched:     glo5 = 0
                .line_patch = BASIC_HOOK_SET_VAR_IMMEDIATE(0x1d, 0)
            },
            // Prevent the yes/no box to choose the light gem from appearing.
            {
                .line_num = 92,
                // Original:    glo12 = HT_Text_ASK_GEM
                // Patched:     CALLPROC play
                .line_patch = BASIC_HOOK_CALL_PROC(0x2)
            },
            {
                .line_num = 93,
                // Original:    CALLPROC play
                // Patched:     TALKCAMERA 0
                .line_patch = BASIC_HOOK_TALK_CAMERA(0)
            },
            {
                .line_num = 94,
                // Original:    CALLPROC quiz
                // Patched:     TALKTOPLAYER 0
                .line_patch = BASIC_HOOK_TALK_TO_PLAYER(0)
            },
            {
                .line_num = 104,
                // Original:    glo12 = HT_Text_ASK_GEM
                // Patched:     TALKCAMERA 0
                .line_patch = BASIC_HOOK_TALK_CAMERA(0)
            },
            {
                .line_num = 105,
                // Original:    CALLPROC quiz
                // Patched:     TALKTOPLAYER 0
                .line_patch = BASIC_HOOK_TALK_TO_PLAYER(0)
            }
        }
    },
    // Ice Citadel Sgt. Byrd
    {
        .trig_index = 48,
        .map_index = 33,
        .num_lines = 3,
        .patches = reusable_patch_1
    },
    // Molten Mount Sgt. Byrd
    {
        .trig_index = 94,
        .map_index = 60,
        .num_lines = 6,
        .patches = reusable_patch_2
    }
};
#pragma endregion
