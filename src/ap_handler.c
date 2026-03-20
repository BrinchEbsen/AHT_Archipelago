#include <ap_handler.h>
#include <ap_settings.h>
#include <ap_patch.h>
#include <ap_notification.h>
#include <system.h>
#include <pad.h>
#include <gamestate.h>
#include <map.h>
#include <hashcodes.h>
#include <ap_collectables.h>
#include <paneldraw.h>
#include <igstdlib.h>
#include <minimap_status.h>
#include <gameloop.h>

// #define AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
// #define AP_DEBUG_NOTIFICATION

#ifdef AP_QUICK_START
#pragma message ( "COMPILING WITH AP_QUICK_START, DO NOT RELEASE" )
#endif

#ifdef AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
#pragma message ( "COMPILING WITH AP_DEBUG_ADD_REMOVE_SHOP_ITEMS, DO NOT RELEASE" )
#endif

#ifdef AP_DEBUG_NOTIFICATION
#pragma message ( "COMPILING WITH AP_DEBUG_NOTIFICATION, DO NOT RELEASE" )
#endif

#define NUM_NEW_GAME_OBJECTIVES 15
EXHashCode new_game_objectives[] = {
    // Realm introduction cutscenes
    HT_Objective_OpeningMovie,
    HT_Objective_SeenIntro_R1A,
    HT_Objective_SeenIntroR2A,
    HT_Objective_SeenProfStartR2A,
    HT_Objective_SeenIntroR3A,
    HT_Objective_SeenProfStartR3A,
    HT_Objective_SeenIntroR4A,
    HT_Objective_ProfGoneToFindRed,

    // Opened starting gate
    HT_Objective_R1A_OpenLockPickerSwitch,
    
    // Zoe intro cutscene
    HT_Objective_R1A_MetZoe,

    // Met the mammoth and rescued Spyro.
    // This is to prevent the gate into Gloomy Glacier from being present,
    // and to allow access to Gloomy Glacier at the player's discretion.
    HT_Objective_3A_MetMonsterMammoth,
    HT_Objective_3B_HunterRescuedSpyro,

    // Moneybags intro
    HT_Objective_MoneybagsGems_1A,
    HT_Objective_Moneybagsintro_1A,
    HT_Objective_GainedLockPicker,
};

#define NUM_REALM_TELEPORTER_MAPORDERINFO 3
MapOrderInfo realm_teleporter_maporderinfo[] = {
    { .m_FileHash = HT_File_Realm2A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm3A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm4A,    .m_MapHash = 0xFFFFFFFF }
};

bool replenish_butterfly_jar = false;

bool draw_cost_text = false;
CostTextType cost_text_type = LightGem;
int cost_text_amt = 0;

void ap_update()
{
    if (g_patch_ap_settings.patch_been_written_to && (gGameLoop.m_State == Running)) {
        ap_gamestate_update();
    }

    ONCE {
        print_interface_addresses();
    }
}

void ap_gamestate_update()
{
    if (g_gamestate_ap_settings.init != AP_SETTINGS_INIT_MAGICVALUE) {
        ap_init_gamestate();
    }

    if (g_gamestate_ap_settings.xls_shop_rowcount > 0)
    {
        // Freeze double gem timer if enabled
        if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_DOUBLE_GEM) != 0)
        {
            static float freeze = 60.0f * 60.0f * 60.0f; // 1 hour
            gGameState.m_PlayerState.m_DoubleGemTimerMax = freeze;
            gGameState.m_PlayerState.m_DoubleGemTimer = freeze;
        }

        // Freeze max values for lock picks and breath ammo
        gGameState.m_PlayerState.m_LockPickers_Max = 127;
        gGameState.m_PlayerState.m_FlameBombs_Max = 127;
        gGameState.m_PlayerState.m_IceBombs_Max = 127;
        gGameState.m_PlayerState.m_WaterBombs_Max = 127;
        gGameState.m_PlayerState.m_ElectricBombs_Max = 127;
    }

    #ifdef AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
    if (g_pad_button_state(PAD_BUTTON_B)) {
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_RIGHT)) {
            dbg_add_shop_item();
        } else if (g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT)) {
            dbg_remove_shop_item();
        }
    }
    #endif

    #ifdef AP_DEBUG_NOTIFICATION
    if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
        ap_set_notification(60*5, COLOR_WHITE,
            "Test notification! The notification that tests things! Something testy happened, probably!");
    }
    #endif
}

#ifdef AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
void dbg_add_shop_item()
{
    int index = g_gamestate_ap_settings.xls_shop_rowcount;
    if (index >= SHOP_TOTAL_NUM_ENTRIES) {
        return;
    }

    xlsShoppingItem* item = &g_gamestate_ap_settings.xls_shop_items[index];

    item->Entity = HT_Entity_Lockpicker;
    item->File = HT_File_Panel;
    item->ItemText = AP_TEXT_ENTRY_HASHCODE_BASE + index-1;
    item->DescText = AP_TEXT_ENTRY_HASHCODE_BASE + index-1;
    item->cost[0] = 1;
    item->cost[1] = 1;
    item->Count = 1;
    item->Num = 0;
    item->AvailableFlags = 0;
    item->BroughtFlags = 0;

    g_gamestate_ap_settings.shop_text[index-1].been_bought = false;
    char* shoptext = g_gamestate_ap_settings.shop_text[index-1].text;
    sprintf(shoptext, "Example check item %d", index);
    
    PRINTF("Added item %d\n", index);

    g_gamestate_ap_settings.xls_shop_rowcount++;
}
void dbg_remove_shop_item()
{
    int index = g_gamestate_ap_settings.xls_shop_rowcount;
    if (index <= 1) {
        return;
    }
    
    PRINTF("Removed item %d\n", index);

    g_gamestate_ap_settings.xls_shop_rowcount--;
}
#endif

void ap_draw(void* pWnd)
{
    if ((gGameLoop.m_State == Running) && !gGameLoop.m_GameIsPaused)
    {
        ap_draw_notification(pWnd);

        if (draw_cost_text) {
            ap_draw_cost_text(pWnd, cost_text_type, cost_text_amt);
            draw_cost_text = false;
        }
    }
}

void ap_draw_cost_text(void* pWnd, CostTextType type, int amt)
{
    char* type_text;

    switch (type) {
        case COST_LightGem:
            if (gGameState.m_PlayerState.m_TotalLightGems >= amt) {
                return;
            }
            type_text = "Light Gems";
            break;
        case COST_DarkGem:
            if (gGameState.m_PlayerState.m_TotalDarkGems >= amt) {
                return;
            }
            type_text = "Dark Gems";
            break;
        default:
            return;
    }

    TEXT_PRINT_ALIGN_COLOR_F(pWnd, 0, 0, Centre, COLOR_LIGHT_RED,
        "Cost: %d %s", amt, type_text);
}

void ap_init_gamestate()
{
    memcpy(&g_gamestate_ap_settings, &g_patch_ap_settings, sizeof(APSettings));

    g_gamestate_ap_settings.init = AP_SETTINGS_INIT_MAGICVALUE;

    #ifdef AP_QUICK_START
    gGameState.m_PlayerState.m_AbilityFlags |= (
        ABILITY_AP_FIREBREATH |
        ABILITY_AP_GLIDE |
        ABILITY_AP_CHARGE |
        ABILITY_AP_SWIM |
        ABILITY_DOUBLE_JUMP
    );
    #endif

    if (g_gamestate_ap_settings.allow_immediate_realm_access) {
        for (int i = 0; i < NUM_REALM_TELEPORTER_MAPORDERINFO; i++) {
            MiniMapStatus__SetBitName(
                &gMiniMapStatus, &realm_teleporter_maporderinfo[i], Selectable);
        }
    }

    // Set starting game objectives
    for (int i = 0; i < NUM_NEW_GAME_OBJECTIVES; i++) {
        PlayerObjectives__SetObjective__ReImplHook(
            &gGameState.m_PlayerObjectives, new_game_objectives[i]);
    }

    // Set objective flag for having bought a lock pick
    gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_BOUGHT_LOCK_PICK;

    PRINTF("Gamestate initialized!\n");
}

bool TeleportPad_PlayerObjectives__GetObjective_PreCallHook(
    PlayerObjectives* self, EXHashCode hashcode, s32* result)
{
    if (g_gamestate_ap_settings.allow_immediate_realm_access) {
        *result = 1;
        return true;
    }

    return PlayerObjectives__GetObjective__ReImplHook(self, hashcode, result);
}

void ap_set_grabbable(u16 map_index, u16 trigger_index)
{
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->union_type != APC_Grabbable) {
            continue;
        }

        if ((coll->grabbable.map_index == map_index) &&
            (coll->grabbable.trigger_index == trigger_index)) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_objective(EXHashCode objective)
{
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->union_type != APC_Objective) {
            continue;
        }

        if (coll->objective.objective == objective) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_location(int index)
{
    int byte = index / 8;
    int bit = index % 8;

    u8* val = &g_gamestate_ap_settings.location_bitfield[byte];

    if (((*val) & (1 << bit)) == 0) {
        (*val) |= (1 << bit);
        PRINTF("[AP] Set location flag index %d\n", index);
    }
}

/*
int ap_binary_search_grabbable(u16 map_index, u16 trigger_index)
{
    int start = AP_GRABBABLE_START;
    int end = AP_GRABBABLE_START + AP_GRABBABLE_NUM - 1;

    while (start <= end) {
        int index = start + ((end-start)/2);
        APCollectable* curr = &g_ap_collectables[index];

        if ((map_index == curr->grabbable.map_index) &&
            (trigger_index == curr->grabbable.trigger_index)) {
            return index;
        }

        if ((map_index < curr->grabbable.map_index) ||
            ((map_index == curr->grabbable.map_index) &&
            (trigger_index < curr->grabbable.trigger_index))) {
            end = index - 1;
        } else {
            start = index + 1;
        }
    }

    return -1;
}
*/

void print_interface_addresses()
{
    PRINTF("PATCH AREA:\n");
    print_apsettings_addresses(&g_patch_ap_settings);
    PRINTF("-----\nGAMESTATE AREA:\n");
    print_apsettings_addresses(&g_gamestate_ap_settings);
    PRINTF("-----\nNOTIFICATION:\n");
    PRINTF("RGBA ap_notification_color: %x\n", &ap_notification_color);
    PRINTF("u32 ap_notification_timer: %x\n", &ap_notification_timer);
    PRINTF("char[%d] ap_notification_text_buffer: %x\n", AP_NOTIFICATION_TEXT_BUFFER_SIZE, &ap_notification_text_buffer);
    PRINTF("-----\n");
}

void print_apsettings_addresses(APSettings* psettings)
{
    PRINTF("u8 location_bitfield[%d]: %x\n", AP_SETTINGS_LOCATIONS_BITFIELD_SIZE, &psettings->location_bitfield);
    PRINTF("u8 num_gem_packs_received: %x\n", &psettings->num_gem_packs_received);
    PRINTF("u8 num_lock_picks_received: %x\n", &psettings->num_lock_picks_received);
    PRINTF("u8 num_fire_ammo_received: %x\n", &psettings->num_fire_ammo_received);
    PRINTF("u8 num_electric_ammo_received: %x\n", &psettings->num_electric_ammo_received);
    PRINTF("u8 num_water_ammo_received: %x\n", &psettings->num_water_ammo_received);
    PRINTF("u8 num_ice_ammo_received: %x\n", &psettings->num_ice_ammo_received);
    PRINTF("bool deathlink_ingoing: %x\n", &psettings->deathlink_ingoing);
    PRINTF("bool deathlink_outgoing: %x\n", &psettings->deathlink_outgoing);
    PRINTF("bool infinite_butterfly_jar: %x\n", &psettings->infinite_butterfly_jar);
    PRINTF("bool skip_cutscene_button: %x\n", &psettings->skip_cutscene_button);
    PRINTF("bool allow_teleport_to_hub: %x\n", &psettings->allow_teleport_to_hub);
    PRINTF("bool allow_immediate_realm_access: %x\n", &psettings->allow_immediate_realm_access);
    PRINTF("bool disable_popups: %x\n", &psettings->disable_popups);
    PRINTF("bool patch_been_written_to: %x\n", &psettings->patch_been_written_to);
    PRINTF("u32 mw_seed: %x\n", &psettings->mw_seed);
    PRINTF("u32 init: %x\n", &psettings->init);
    PRINTF("u8[4] boss_costs: %x\n", &psettings->boss_costs);
    PRINTF("u8[4] lg_door_costs: %x\n", &psettings->lg_door_costs);
    PRINTF("int xls_shop_sheetcount_ALWAYS_1: %x\n", &psettings->xls_shop_sheetcount_ALWAYS_1);
    PRINTF("int xls_shop_sheet_offset_ALWAYS_4: %x\n", &psettings->xls_shop_sheet_offset_ALWAYS_4);
    PRINTF("int xls_shop_rowcount: %x\n", &psettings->xls_shop_rowcount);
    PRINTF("xlsShoppingItem[%d] xls_shop_items: %x\n", SHOP_TOTAL_NUM_ENTRIES, &psettings->xls_shop_items);
    PRINTF("APSettings_TextEntry[%d] shop_text: %x\n", SHOP_TOTAL_NUM_ENTRIES - SHOP_NUM_VANILLA_ENTRIES, &psettings->shop_text);
}

int XSEItemHandler_Player__InitialiseStart_PreCallHook(void* self)
{
    if (replenish_butterfly_jar)
    {
        replenish_butterfly_jar = false;
        gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_BUTTERFLY_JAR;
    }

    return XSEItemHandler_Player__InitialiseStart(self);
}

void Player_urghhhImDead_PostHook()
{
    if (g_gamestate_ap_settings.xls_shop_rowcount == 0)
    {
        return;
    }

    if (g_gamestate_ap_settings.infinite_butterfly_jar)
    {
        replenish_butterfly_jar = true;
    }
}

int Popup__Update_VtableHook(void* self)
{
    if (g_gamestate_ap_settings.disable_popups)
    {
        return -1;
    }

    return Popup__Update(self);
}

s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow *self)
{
    if (gp_paneldraw_loop == NULL) {
        GUI_Base* paneldraw = paneldraw_create();
        if (paneldraw != NULL) {
            paneldraw_callback = ap_draw;
        }
    }

    ap_update();

    return SEGameFlow__v_StateRunning(self);
}
