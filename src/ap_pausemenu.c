#include <util.h>
#include <ap_pausemenu.h>
#include <pad.h>
#include <paneldraw.h>
#include <map.h>
#include <gameloop.h>
#include <system.h>
#include <hashcodes.h>
#include <gamestate.h>
#include <ap_settings.h>
#include <ap_notification.h>
#include <ap_keyring.h>
#include <ap_minimap.h>

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

int curr_page = 0;
static inline void next_page()
{
    curr_page++;
    
    if (!AP_GAMESTATE_USE_KEY_RINGS && (curr_page == PauseMenu_Keyrings)) {
        curr_page++;
    }

    if (curr_page >= PauseMenu_NUM) {
        curr_page = 0;
    }
}
static inline void prev_page()
{
    curr_page--;
    
    if (!AP_GAMESTATE_USE_KEY_RINGS && (curr_page == PauseMenu_Keyrings)) {
        curr_page--;
    }

    if (curr_page < 0) {
        curr_page = (int)PauseMenu_NUM - 1;
    }
}

s32 GUI_PauseMenu__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd)
{
    if (do_pause_menu_controls()) {
        if (g_gamestate_ap_settings.allow_teleport_to_hub) {
            draw_teleport_menu(self, pWnd);
        }
    
        draw_pause_stats(self, pWnd);
        draw_notification_toggle(self, pWnd);
        draw_map_icon_toggle(self, pWnd);
    } else {
        TEXT_PRINT_ALIGN_COLOR(pWnd, 0, 0, BottomCentre, COLOR_RED, "Archipelago gamestate not initialized!");
    }

    return GUI_PauseMenu__v_DrawStateRunning(self, pWnd);
}

s32 GUI_PauseMenu__v_StateRunning_VtableHook(GUI_Base* self)
{
    if (do_pause_menu_controls()) {
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
    
        if (g_pad_button_edge_down(PAD_BUTTON_X)) {
            show_notifications = !show_notifications;
        }
        if (g_pad_button_edge_down(PAD_BUTTON_B)) {
            g_show_minimap_icons = !g_show_minimap_icons;
        }
    
        if (g_pad_button_edge_down(PAD_BUTTON_L) || g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT)) {
            prev_page();
        } else if (g_pad_button_edge_down(PAD_BUTTON_R) || g_pad_button_edge_down(PAD_BUTTON_DPAD_RIGHT)) {
            next_page();
        }
    }

    return GUI_PauseMenu__v_StateRunning(self);
}

bool do_pause_menu_controls()
{
    return g_gamestate_ap_settings.init == AP_SETTINGS_INIT_MAGICVALUE;
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

void draw_pause_stats(GUI_Base* self, void* pWnd)
{
    u16 x = 3;
    u16 y = 40;
    static u16 spacing = 20;

    EXRect r = {
        .x = 0,
        .y = y,
        .w = 140,
        .h = 345
    };

    XWnd__DrawRect(pWnd, &r, COLOR_RGBA(0, 0, 0, 0x20));

    RGBA on_col = COLOR_WHITE;
    RGBA off_col = COLOR_RGBA(0x40, 0x40, 0x40, 0x80);

    switch (curr_page)
    {
        case PauseMenu_Abilities:
            draw_stats_abilities(self, pWnd, x, y, spacing, on_col, off_col);
            break;
        case PauseMenu_Keyrings:
            draw_stats_keyrings(self, pWnd, x, y, spacing, on_col, off_col);
            break;
        case PauseMenu_Realms:
            draw_stats_realms(self, pWnd, x, y, spacing, on_col, off_col);
            break;
        default:
            break;
    }
}

void draw_stats_abilities(GUI_Base* self, void *pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col)
{
    RGBA* col;
    u32 abiflg = gGameState.m_PlayerState.m_AbilityFlags;

    col = ((abiflg & ABILITY_DOUBLE_JUMP) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Double Jump");
    y += spacing;

    col = ((abiflg & ABILITY_POLE_SPIN) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Pole Spin");
    y += spacing;

    col = ((abiflg & ABILITY_HIT_POINT_UPGRADE) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Health Unit+");
    y += spacing;

    col = g_gamestate_ap_settings.infinite_butterfly_jar ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Health Refill");
    y += spacing;

    col = ((abiflg & ABILITY_AP_FIREBREATH) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Fire Breath");
    y += spacing;

    col = ((abiflg & ABILITY_ELECTRIC_BREATH) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Electric Breath");
    y += spacing;

    col = ((abiflg & ABILITY_WATER_BREATH) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Water Breath");
    y += spacing;

    col = ((abiflg & ABILITY_ICE_BREATH) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Ice Breath");
    y += spacing;

    col = ((abiflg & ABILITY_WING_SHIELD) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Wing Shield");
    y += spacing;

    col = ((abiflg & ABILITY_WALL_KICK) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Wall Kick");
    y += spacing;

    col = ((abiflg & ABILITY_HORN_DIVE_UPGRADE) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Shockwave");
    y += spacing;

    col = ((abiflg & ABILITY_AP_GLIDE) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Glide");
    y += spacing;

    col = ((abiflg & ABILITY_AP_CHARGE) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Charge");
    y += spacing;

    col = ((abiflg & ABILITY_AP_SWIM) != 0) ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Swim");
    y += spacing;

    if (!AP_GAMESTATE_USE_KEY_RINGS) {
        s8 lock_pickers = gGameState.m_PlayerState.m_LockPickers;
        col = (lock_pickers > 0) ? &on_col : &off_col;
        TEXT_PRINT_ALIGN_COLOR_F(pWnd, x, y, TopLeft, *col, "Lock Picks: %d", lock_pickers);
    }
    y += spacing*2;

    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, on_col, "<L Abilities R>");
}

void draw_stats_keyrings(GUI_Base* self, void *pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col)
{
    RGBA* col;
    u8* keyrings = g_gamestate_ap_settings.keyring_bitfield;

    for (int i = 0; i < AP_NUM_KEYRINGS; i++) {
        col = get_u8_bitfield_value(keyrings, i) ? &on_col : &off_col;
        TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, g_ap_keyring_pausemenu_strings[i]);
        y += spacing;
    }

    y += spacing*2;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, on_col, "<L Key Rings R>");
}

void draw_stats_realms(GUI_Base* self, void* pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col)
{
    RGBA* col;

    col = g_gamestate_ap_settings.realm_access[0] ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Dragon Kingdom");
    y += spacing;

    col = g_gamestate_ap_settings.realm_access[1] ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Lost Cities");
    y += spacing;

    col = g_gamestate_ap_settings.realm_access[2] ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Icy Wilderness");
    y += spacing;

    col = g_gamestate_ap_settings.realm_access[3] ? &on_col : &off_col;
    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, *col, "Volcanic Isle");
    y += spacing*13;

    TEXT_PRINT_ALIGN_COLOR(pWnd, x, y, TopLeft, on_col, "<L Realms R>");
}

void draw_notification_toggle(GUI_Base* self, void* pWnd)
{
    EXRect r = {
        .x = 0,
        .y = 0,
        .w = (WND_WIDTH/2)-2,
        .h = 37
    };

    XWnd__DrawRect(pWnd, &r, COLOR_RGBA(0, 0, 0, 0x20));

    textprintf(pWnd, 2, 2, 1.0f, TopLeft, COLOR_WHITE, true,
        "~B Show Notifications: %s", show_notifications ? "Yes" : "No");
}

void draw_map_icon_toggle(GUI_Base* self, void* pWnd)
{
    EXRect r = {
        .x = (WND_WIDTH/2)+2,
        .y = 0,
        .w = (WND_WIDTH/2)-2,
        .h = 37
    };

    XWnd__DrawRect(pWnd, &r, COLOR_RGBA(0, 0, 0, 0x20));

    textprintf(pWnd, (WND_WIDTH/2)+4, 2, 1.0f, TopLeft, COLOR_WHITE, true,
        "~Y Show Map Icons: %s", g_show_minimap_icons ? "Yes" : "No");
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

        s32 goto_map_index = -1;
        // Test which realm the current map is in
        for (int j = 0; j < entry->num_maps; j++) {
            if (*(entry->maps + j) == curr_map->m_MapListIndex) {
                goto_map_index = entry->map_index;
            }
        }

        if (goto_map_index != -1) {
            SE_Map* goto_map = gMapList.m_List[goto_map_index].m_pMap;
            goto_map->m_GameState->m_LastStartPoint = entry->startpoint;
            goto_map->m_GameState->m_LastStartPointPlayer = Player_Spyro;
            gGameState.m_StartMapIndex = goto_map_index;
            PlayerState__RestartGame(&gGameState.m_PlayerState);

            // Reset bosses to make sure they don't bug out when you return

            s32 beaten_obj;

            // Gnasty Gnorc
            PlayerObjectives__GetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, HT_Objective_Boss1_Beaten, &beaten_obj);
            if (beaten_obj == 0) {
                gMapList.m_List[32].m_pMap->m_GameState->m_LastStartPoint = HT_StartPoint_START;
            }
            
            // Ineptune
            PlayerObjectives__GetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, HT_Objective_Boss2_Beaten, &beaten_obj);
            if (beaten_obj == 0) {
                PlayerObjectives__ClearObjective(
                    &gGameState.m_PlayerObjectives, HT_Objective_SeenIneptuneIntro);
            }
            
            // Red
            PlayerObjectives__GetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, HT_Objective_Boss3_Beaten, &beaten_obj);
            if (beaten_obj == 0) {
                gMapList.m_List[41].m_pMap->m_GameState->m_LastStartPoint = HT_StartPoint_Restart1;
            }
            
            // Mecha Red
            PlayerObjectives__GetObjective__ReImplHook(
                &gGameState.m_PlayerObjectives, HT_Objective_Boss4_Beaten, &beaten_obj);
            if (beaten_obj == 0) {
                gMapList.m_List[34].m_pMap->m_GameState->m_LastStartPoint = HT_StartPoint_START;
            }

            break;
        }
    }
}
