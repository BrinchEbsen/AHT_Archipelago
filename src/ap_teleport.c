#include <ap_teleport.h>
#include <pad.h>
#include <paneldraw.h>
#include <map.h>
#include <gameloop.h>
#include <system.h>
#include <hashcodes.h>
#include <gamestate.h>
#include <ap_settings.h>

#define AP_TELEPORT_CLOSE_TIMER_MAX 60

int close_timer = 0;

int realm1_map_indexes[] = {
    2,  // Blinky MiniGame (MR1_Blk)
    3,  // SrgBird MiniGame (MR1_Sgt)
    4,  // Sparx MiniGame (MR1_Spx)
    5,  // Swamp Attack (MR1_Spy)
    22, // Dragon Shores (Realm1C)
    23, // Dragon Swamp (Realm1B)
    24, // Dragon Village (Hub Realm1A)
    25, // Map_R1LinkAB
    26, // Map_R1LinkAC
    32  // Gnasty Gnorc (Realm1Z)
};
#define NUM_REALM1_MAPS 10

int realm2_map_indexes[] = {
    6,  // Blinky MiniGame (MR2_Blk)
    7,  // SrgBird MiniGame (MR2_Sgt)
    8,  // Sparx MiniGame (MR2_Spx)
    9,  // Turtle MiniGame (MR2_Spy)
    19, // Sunken City (Realm2B)
    20, // Cloud City (Realm2C)
    21, // Cloud City Ball Gadget (Realm2C)
    45, // The Beach (Hub Realm2A)
    46, // Map_R2LinkAB
    47, // Map_R2LinkAC
    64  // Watery Tomb (Realm2Z)
};
#define NUM_REALM2_MAPS 11

int realm3_map_indexes[] = {
    10, // Blinky MiniGame (MR3_Blk)
    11, // SrgBird MiniGame (MR3_Sgt)
    12, // Sparx MiniGame (MR3_Spx)
    13, // Spyro MiniGame (MR3_Spy)
    31, // Frostbite Village (Hub Realm3A)
    33, // Ice Citadel (Realm3C)
    35, // Mountain Pass (Realm3B)
    41  // Red's Chamber (Realm3Z)
};
#define NUM_REALM3_MAPS 8

int realm4_map_indexes[] = {
    14, // Blinky MiniGame (MR4_Blk)
    15, // SrgBird MiniGame (MR4_Sgt)
    16, // Sparx MiniGame (MR4_Spx)
    17, // Spyro MiniGame (MR4_Spy)
    30, // Mine & Foundry (Realm4D)
    34, // MechaRed (Realm4Z)
    40, // Professors Laboratory (Realm4E)
    44, // Stormy Beach (Realm4A)
    57, // Map_R4LinkBC
    58, // Map_R4LinkCD
    59, // Map_R4LinkDE
    60, // Volcano Ascent (Realm4B)
    61, // Volcano Descent 1 (Realm4C)
    62, // Volcano Descent 2 (Realm4C)
    63  // Volcano Descent 3 (Realm4C)
};
#define NUM_REALM4_MAPS 15

typedef struct HUBCentreEntry
{
    int map_index;
    int* maps;
    int num_maps;
    EXHashCode file;
    EXHashCode map;
    EXHashCode startpoint;
} HUBCentreEntry;

#define NUM_HUB_CENTERS 4
HUBCentreEntry hub_centers[] = {
    {
        .map_index = 24,
        .maps = realm1_map_indexes,
        .num_maps = NUM_REALM1_MAPS,
        .file = HT_File_Realm1A,
        .map = HT_Map_Main,
        .startpoint = HT_StartPoint_START
    },
    {
        .map_index = 45,
        .maps = realm2_map_indexes,
        .num_maps = NUM_REALM2_MAPS,
        .file = HT_File_Realm2A,
        .map = 0,
        .startpoint = HT_StartPoint_START
    },
    {
        .map_index = 31,
        .maps = realm3_map_indexes,
        .num_maps = NUM_REALM3_MAPS,
        .file = HT_File_Realm3A,
        .map = HT_Map_Main,
        .startpoint = HT_StartPoint_START
    },
    {
        .map_index = 44,
        .maps = realm4_map_indexes,
        .num_maps = NUM_REALM4_MAPS,
        .file = HT_File_Realm4A,
        .map = 0,
        .startpoint = HT_StartPoint_START
    }
};

s32 GUI_PauseMenu__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd)
{
    if (g_gamestate_ap_settings.allow_teleport_to_hub) {
        draw_teleport_menu(self, pWnd);
    }

    return GUI_PauseMenu__v_DrawStateRunning(self, pWnd);
}

s32 GUI_PauseMenu__v_StateRunning_VtableHook(GUI_Base* self)
{
    if (g_gamestate_ap_settings.allow_teleport_to_hub) {
        if (g_pad_button_state(PAD_BUTTON_Y)) {
            close_timer++;

            if (close_timer >= AP_TELEPORT_CLOSE_TIMER_MAX) {
                close_pause_menu(self);
                teleport_to_hub();
            }
        } else {
            close_timer = 0;
        }
    }

    return GUI_PauseMenu__v_StateRunning(self);
}

void draw_teleport_menu(GUI_Base* self, void* pWnd)
{
    TEXT_PRINT_ALIGN(pWnd, 35, 0, BottomCentre, "Hold ~X to teleport to HUB");

    if (close_timer <= 0) {
        return;
    }

    EXRect bgrect = {
        .x = WND_WIDTH / 4,
        .y = WND_HEIGHT - 20,
        .w = WND_WIDTH / 2,
        .h = 15
    };

    float ratio = (float)close_timer / (float)AP_TELEPORT_CLOSE_TIMER_MAX;
    if (ratio > 1) {
        ratio = 1.0f;
    }

    EXRect redrect = {
        .x = bgrect.x,
        .y = bgrect.y,
        .w = bgrect.w * ratio,
        .h = bgrect.h
    };

    XWnd__DrawRect(pWnd, &bgrect, COLOR_BLACK);
    XWnd__DrawRect(pWnd, &redrect, COLOR_RED);
}

void close_pause_menu(GUI_Base* self)
{
    u32 menuflg = GUI_MENU__M_MENUFLAGS(self) & 1;
    GUI_MENU__M_MENUFLAGS(self) = menuflg;
    if (menuflg == 0) {
        return;
    }

    if ((self->m_Flags_SE_Loop & 1) != 0) {
        return;
    }

    SE_Loop__RequestClose_func requestclose_func = self->__vtable->RequestClose.__pfn;
    requestclose_func((SE_Loop*)self, 0);
}

void teleport_to_hub()
{
    SE_Map* curr_map = GetSpyroMap(0);
    
    for (int i = 0; i < NUM_HUB_CENTERS; i++) {
        HUBCentreEntry* entry = &hub_centers[i];

        SE_Map* goto_map = NULL;
        // Test which realm the current map is in
        for (int j = 0; j < entry->num_maps; j++) {
            if (*(entry->maps + j) == curr_map->m_MapListIndex) {
                goto_map = gMapList.m_List[entry->map_index].m_pMap;
                break;
            }
        }

        if (goto_map != NULL) {
            SE_GameLoop__GoToMap(&gGameLoop, entry->file, entry->startpoint, entry->map);
            SE_Map__SetLastStartPoint(goto_map, entry->startpoint, Player_Spyro);
            break;
        }
    }
}
