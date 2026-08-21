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
#include <minimap_status.h>
#include <map_minigame.h>

#define AP_TELEPORT_CLOSE_TIMER_MAX 60

int close_timer = 0;

bool instant_shop_opening = false;
char* instant_shop_cannot_open_reason = NULL;

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

void draw_menu_rect(void* pWnd, EXRect* r)
{
    XWnd__DrawRect(pWnd, r, COLOR_RGBA(0, 0, 0, 0x20));
    XWnd__DrawGraduatedRectOutline(pWnd, r,
        COLOR_HEX(0x9340BC),
        COLOR_RGBA(0, 0, 0, 0),
    3, RECT_SIDE_ALL);
}

s32 GUI_PauseMenu__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd)
{
    if (do_pause_menu_controls()) {
        if (g_gamestate_ap_settings.instant_teleport_mode == AP_TELEPORT_MODE_TP_TO_HUB) {
            draw_teleport_menu(self, pWnd);
        } else if (g_gamestate_ap_settings.instant_teleport_mode == AP_TELEPORT_MODE_SHOP_ANYWHERE) {
            draw_instant_shop_menu(self, pWnd);
        }
    
        draw_pause_stats(self, pWnd);
        draw_notification_toggle(self, pWnd);
        draw_ut_stats(self, pWnd);
        draw_checks_percentage(self, pWnd);
        if (g_gamestate_ap_settings.deathlink_deaths_before_send > 1)
        {
            draw_deathlink_count(self, pWnd);
        }
    } else {
        TEXT_PRINT_ALIGN_COLOR(pWnd, 0, 0, BottomCentre, COLOR_RED, "Archipelago gamestate not initialized!");
    }

    return GUI_PauseMenu__v_DrawStateRunning(self, pWnd);
}

s32 GUI_PauseMenu__v_StateRunning_VtableHook(GUI_Base* self)
{
    if (do_pause_menu_controls()) {
        if (g_gamestate_ap_settings.instant_teleport_mode == AP_TELEPORT_MODE_TP_TO_HUB) {
            if (g_pad_button_state(PAD_BUTTON_Y)) {
                close_timer++;
    
                if (close_timer >= AP_TELEPORT_CLOSE_TIMER_MAX) {
                    close_pause_menu(self);
                    teleport_to_hub();
                }
            } else {
                close_timer = 0;
            }
        } else if (g_gamestate_ap_settings.instant_teleport_mode == AP_TELEPORT_MODE_SHOP_ANYWHERE) {
            char* reason = NULL;

            if (can_start_shop_sequence(&reason)) {
                if (g_pad_button_edge_down(PAD_BUTTON_Y))
                {
                    close_pause_menu(self);
                    gMiniMapStatus.m_CurrentShopRestart = 0;
                    PanelShop__OpenShop(gpPanelShop, false);
                    instant_shop_opening = true;
                }
            }

            instant_shop_cannot_open_reason = reason;
        }
    
        if (g_pad_button_edge_down(PAD_BUTTON_X)) {
            show_notifications = !show_notifications;
        }
    
        if (g_pad_button_edge_down(PAD_BUTTON_L) || g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT)) {
            prev_page();
        } else if (g_pad_button_edge_down(PAD_BUTTON_R) || g_pad_button_edge_down(PAD_BUTTON_DPAD_RIGHT)) {
            next_page();
        }
    }

    return GUI_PauseMenu__v_StateRunning(self);
}

bool can_start_shop_sequence(char** reason)
{
    *reason = NULL;

    static char str_already_opening_shop[] = "Already opening shop";
    static char str_player_is_unloaded[] = "Player is unloaded";
    static char str_player_isnt_spyro[] = "Player isn't Spyro";
    static char str_not_idle_on_ground[] = "Not idle on ground";

    if (instant_shop_opening)
    {
        *reason = str_already_opening_shop;
        return false;
    }

    if (gpPlayer == NULL)
    {
        *reason = str_player_is_unloaded;
        return false;
    }

    Players curr_player = XSEItemHandler_Player__M_PLAYERTYPE(gpPlayer);
    if ((curr_player != Player_Spyro) && (curr_player != Player_Flame) && (curr_player != Player_Ember))
    {
        *reason = str_player_isnt_spyro;
        return false;
    }

    PStateFlags state_flags = XSEItemHandler_Player__M_PLAYERSTATEFLAGS(gpPlayer);
    if ((state_flags & ps_Shopping) != 0)
    {
        *reason = str_already_opening_shop;
        return false;
    }

    PlayerModes mode = XSEItemHandler_Player__M_PLAYERMODE(gpPlayer);
    switch (mode)
    {
        case breathe:
            break;
        case walk:
            break;
        case idleSparx:
            break;
        default:
            *reason = str_not_idle_on_ground;
            return false;
    }

    return true;
}

void handle_instant_shop_sequence()
{
    // Wait until the game is unpaused, then pause.
    if (!gGameLoop.m_GameIsPaused)
    {
        SE_GameLoop__GameSetPauseOn(&gGameLoop, 0);
        instant_shop_opening = false;
    }
}

bool do_pause_menu_controls()
{
    return g_gamestate_ap_settings.init == AP_SETTINGS_INIT_MAGICVALUE;
}

void draw_teleport_menu(GUI_Base* self, void* pWnd)
{
    TEXT_PRINT_ALIGN(pWnd, 0, 364, TopRight, "Hold ~X to teleport to HUB");

    if (close_timer <= 0) {
        return;
    }

    EXRect bgrect = {
        .x = (WND_WIDTH / 2) - 20,
        .y = WND_HEIGHT - 50,
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

void draw_instant_shop_menu(GUI_Base* self, void* pWnd)
{
    if (instant_shop_cannot_open_reason == NULL)
    {
        TEXT_PRINT_ALIGN(pWnd, 0, 364, TopRight, "Press ~X to open shop");
    }
    else
    {
        TEXT_PRINT_ALIGN(pWnd, 0, 364, TopRight, "Cannot open shop:");
        TEXT_PRINT_ALIGN(pWnd, 0, 384, TopRight, instant_shop_cannot_open_reason);
    }
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

    draw_menu_rect(pWnd, &r);

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
        .w = (WND_WIDTH/2)-1,
        .h = 37
    };

    draw_menu_rect(pWnd, &r);

    textprintf(pWnd, 2, 2, 1.0f, TopLeft, COLOR_WHITE, true,
        "~B Show Notifications: %s", show_notifications ? "Yes" : "No");
}

void draw_ut_stats(GUI_Base* self, void* pWnd)
{
    EXRect r = {
        .x = (WND_WIDTH/2)+1,
        .y = 0,
        .w = (WND_WIDTH/2)-1,
        .h = 37
    };

    if (!g_gamestate_ap_settings.ut_enabled)
    {
        r.h += r.h/2;
    }
    else if (g_gamestate_ap_settings.shop_unlock_mode)
    {
        r.h += r.h;
    }

    draw_menu_rect(pWnd, &r);

    u16 txt_x_base = r.x+4;
    static const u16 txt_y_base = 12;

    if (!g_gamestate_ap_settings.ut_enabled)
    {
        if (g_gamestate_ap_settings.shop_unlock_mode)
        {
            textprint(pWnd, txt_x_base, txt_y_base, 1.0f, TopLeft, COLOR_LIGHT_RED, true,
                "Map Icons & Gem Logic unavailable, UT required.");
        }
        else
        {
            textprint(pWnd, txt_x_base, txt_y_base, 1.0f, TopLeft, COLOR_LIGHT_RED, true,
                "Map Icons unavailable,\nUT required.");
        }
    }
    else
    {
        textprint(pWnd, txt_x_base, txt_y_base, 1.0f, TopLeft, COLOR_WHITE, true,
            "Map Icons Enabled");
        
        if (g_gamestate_ap_settings.shop_unlock_mode)
        {
            s32 gems = gGameState.m_PlayerState.m_Gems;

            // Test if this is a minigame map.
            SE_Map* map = GetSpyroMap(0);
            if (map != NULL)
            {
                GetRuntimeClass_func get_rtc = map->__vtable->GetRuntimeClass.__pfn;
                EXRuntimeClass* rtc = get_rtc();
                if (class_is_or_inherits_from(rtc, &classSEMap_MiniGame))
                {
                    // We add the stored gems to the current count.
                    gems += ((SEMap_MiniGame*)map)->m_StoredGems;
                }
            }

            textprintf(pWnd, txt_x_base, txt_y_base+20, 1.0f, TopLeft, COLOR_WHITE, true,
                "Gems: %d/%d", gems, g_gamestate_ap_settings.total_gems_available);

            textprintf(pWnd, txt_x_base, txt_y_base+40, 1.0f, TopLeft, COLOR_WHITE, true,
                "(%d Required)", g_gamestate_ap_settings.total_gems_in_logic);
        }
    }
}

void draw_checks_percentage(GUI_Base* self, void* pWnd)
{
    int total = 0;
    int collected = 0;

    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++)
    {
        APCollectable* coll = &g_ap_collectables[i];

        if ((coll->type == FireWork) && !g_gamestate_ap_settings.fireworks_are_randomized)
        {
            continue;
        }

        total++;
        collected += get_u8_bitfield_value(g_gamestate_ap_settings.location_bitfield, i*2);
    }

    if (AP_GAMESTATE_SHOP_IS_RANDOMIZED)
    {
        // -1 because of teleport ticket at the start
        for (int i = 0; i < g_gamestate_ap_settings.xls_shop_rowcount-1; i++)
        {
            total++;
            collected += g_gamestate_ap_settings.shop_text[i].been_bought;
        }
    }

    float percentage = ((float)collected / (float)total) * 100.0f;

    EXRect r = {
        .x = 0,
        .y = 40+345+2,
        .w = 140,
        .h = 28
    };

    draw_menu_rect(pWnd, &r);

    textprintf(pWnd, 3, 390, 1.0f, TopLeft, COLOR_WHITE, true, "Checks: %.1f%%", percentage);
}

void draw_deathlink_count(GUI_Base* self, void* pWnd)
{
    EXRect r = {
        .x = 140+2,
        .y = 40,
        .w = (WND_WIDTH/2)-140-3,
        .h = 28
    };

    draw_menu_rect(pWnd, &r);

    u8 death_counter = g_gamestate_ap_settings.deathlink_death_counter;
    u8 death_limit   = g_gamestate_ap_settings.deathlink_deaths_before_send;

    // Make text flash red if you're 1 death away from a deathlink.
    RGBA text_color = COLOR_WHITE;
    if ((death_counter == (death_limit-1)) && ((self->m_UpdateCounter & 0x10) != 0))
    {
        text_color = COLOR_LIGHT_RED;
    }

    textprintf(pWnd, r.x+3, r.y+1, 1.0f, TopLeft, text_color, true, "DL: %u/%u", death_counter, death_limit);
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

            reset_boss_progress();

            break;
        }
    }
}

s32 SE_GameLoop__Teleport_PreCallHook(SE_GameLoop* self, SE_GameState* pGS)
{
    SE_GameLoop__Teleport(self, pGS);
    reset_boss_progress();
}

void reset_boss_progress()
{
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
}
