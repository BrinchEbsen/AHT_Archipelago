#include <util.h>
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
#include <ap_objectives.h>
#include <ap_deathlink.h>

// #define AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
// #define AP_DEBUG_NOTIFICATION
// #define AP_DEBUG_DEATHLINK
// #define AP_DEBUG_COLLECTABLES

#ifdef AP_QUICK_START
#pragma message ( "COMPILING WITH AP_QUICK_START, DO NOT RELEASE" )
#endif

#ifdef AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
#pragma message ( "COMPILING WITH AP_DEBUG_ADD_REMOVE_SHOP_ITEMS, DO NOT RELEASE" )
#endif

#ifdef AP_DEBUG_NOTIFICATION
#pragma message ( "COMPILING WITH AP_DEBUG_NOTIFICATION, DO NOT RELEASE" )
#endif

#ifdef AP_DEBUG_DEATHLINK
#pragma message ( "COMPILING WITH AP_DEBUG_DEATHLINK, DO NOT RELEASE" )
#endif

#ifdef AP_DEBUG_COLLECTABLES
#pragma message ( "COMPILING WITH AP_DEBUG_COLLECTABLES, DO NOT RELEASE" )
#endif

MapOrderInfo realm_teleporter_maporderinfo[] = {
    { .m_FileHash = HT_File_Realm1A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm2A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm3A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm4A,    .m_MapHash = 0xFFFFFFFF }
};

s32 realm_hub_map_indexes[] = {
    24, // Dragon Village
    45, // Coastal Remains
    31, // Frostbite Village
    44  // Stormy Beach
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

    #ifdef AP_DEBUG_COLLECTABLES
    // Prints all locations to the log
    if (g_pad_button_state(PAD_BUTTON_B)) {
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
            for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
                APCollectable* coll = &g_ap_collectables[i];
                switch (coll->union_type) {
                    case APC_Grabbable:
                        PRINTF("[%d]-G | m: %d, t: %d\n",
                            i, coll->grabbable.map_index, coll->grabbable.trigger_index);
                        break;
                    case APC_Objective:
                        PRINTF("[%d]-O | m: %d, t: %d, h: %x\n",
                            i, coll->objective.map_index, coll->objective.trigger_index, coll->objective.objective);
                        break;
                }
            }
        }
    }
    #endif
}

void ap_gamestate_update()
{
    if (!ap_gamestate_is_initialized()) {
        return;
    }

    if (AP_GAMESTATE_SHOP_IS_RANDOMIZED)
    {
        // Freeze double gem timer if enabled
        if ((gGameState.m_PlayerState.m_AbilityFlags & ABILITY_DOUBLE_GEM) != 0)
        {
            static float freeze = 60.0f * 60.0f * 60.0f; // 1 hour
            gGameState.m_PlayerState.m_DoubleGemTimerMax = freeze;
            gGameState.m_PlayerState.m_DoubleGemTimer = freeze;
        }

        // Freeze max values for lock picks and breath ammo
        if (!AP_GAMESTATE_USE_KEY_RINGS) {
            gGameState.m_PlayerState.m_LockPickers_Max = 127;
        }
        gGameState.m_PlayerState.m_FlameBombs_Max = 127;
        gGameState.m_PlayerState.m_IceBombs_Max = 127;
        gGameState.m_PlayerState.m_WaterBombs_Max = 127;
        gGameState.m_PlayerState.m_ElectricBombs_Max = 127;
    }

    if (AP_GAMESTATE_USE_KEY_RINGS) {
        gGameState.m_PlayerState.m_LockPickers = 0;
        gGameState.m_PlayerState.m_LockPickers_Max = 0;
    }

    if (gGameState.m_PlayerState.m_TotalLightGems >= g_gamestate_ap_settings.invincibility_cost) {
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_InvincibilityPowered);
    } else {
        PlayerObjectives__ClearObjective(&gGameState.m_PlayerObjectives, HT_Objective_InvincibilityPowered);
    }

    if (gGameState.m_PlayerState.m_TotalLightGems >= g_gamestate_ap_settings.supercharge_cost) {
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_SuperchargePowered);
    } else {
        PlayerObjectives__ClearObjective(&gGameState.m_PlayerObjectives, HT_Objective_SuperchargePowered);
    }
    
    ap_deathlink_update();

    ap_update_realm_access();

    #ifdef AP_DEBUG_DEATHLINK
    if (g_pad_button_state(PAD_BUTTON_B)) {
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
            g_gamestate_ap_settings.deathlink_ingoing = AP_DEATHLINK_MODE_SHIELDED;
        }
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_RIGHT)) {
            g_gamestate_ap_settings.deathlink_ingoing = AP_DEATHLINK_MODE_FULL;
        }
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT)) {
            g_gamestate_ap_settings.deathlink_outgoing = false;
        }
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_UP)) {
            gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_BUTTERFLY_JAR;
        }
    }
    #endif

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

        #ifdef AP_DEBUG_DEATHLINK
        TEXT_PRINT_ALIGN_COLOR_F(pWnd, 0, 0, CentreLeft, COLOR_LIGHT_RED,
            "DL in: %d\nDL out: %d\nign: %d",
            g_gamestate_ap_settings.deathlink_ingoing,
            g_gamestate_ap_settings.deathlink_outgoing,
            deathlink_ignore_next_death);
        #endif
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
    PRINTF("Initializing gamestate...\n");

    memcpy(&g_gamestate_ap_settings, &g_patch_ap_settings, sizeof(APSettings));
    PRINTF("Copied settings from injected patch.\n");

    #ifdef AP_QUICK_START
    gGameState.m_PlayerState.m_AbilityFlags |= (
        ABILITY_AP_FIREBREATH |
        ABILITY_AP_GLIDE |
        ABILITY_AP_CHARGE |
        ABILITY_AP_SWIM |
        ABILITY_DOUBLE_JUMP
    );
    PRINTF("DEBUG QUICK START!\n");
    #endif

    if (g_gamestate_ap_settings.starting_realm > 3) {
        PRINTF("Invalid starting realm %d, defaulting to 0 (Dragon Village).\n",
            g_gamestate_ap_settings.starting_realm);

        g_gamestate_ap_settings.starting_realm = 0;
    }

    gGameState.m_StartMapIndex = realm_hub_map_indexes[g_gamestate_ap_settings.starting_realm];
    PRINTF("Set starting map index to %d\n", gGameState.m_StartMapIndex);

    MiniMapStatus__SetBitName(
        &gMiniMapStatus,
        &realm_teleporter_maporderinfo[g_gamestate_ap_settings.starting_realm],
        Selectable);

    // Set starting game objectives
    for (int i = 0; i < NUM_NEW_GAME_OBJECTIVES; i++) {
        PlayerObjectives__SetObjective__ReImplHook(
            &gGameState.m_PlayerObjectives, new_game_objectives[i]);
    }
    PRINTF("Set %d objectives.\n", NUM_NEW_GAME_OBJECTIVES);

    // Set objective flag for having bought a lock pick
    gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_BOUGHT_LOCK_PICK;

    ap_set_gamestate_initialized();

    PRINTF("Gamestate initialized!\n");
}

void ap_update_realm_access()
{
    for (int i = 0; i < 4; i++) {
        if (g_gamestate_ap_settings.realm_access[i]) {
            MiniMapStatus__SetBitName(
                &gMiniMapStatus,
                &realm_teleporter_maporderinfo[i],
                Selectable);
        }
    }
}

SE_GameState* mapchanger_SE_GameState__operatorequals_PreCallHook(SE_GameState* self, SE_GameState* _ctor_arg)
{
    // This function copies the save file's gamestate into the current gamestate before the game starts up.
    // We initialize whatever we need to in here.

    SE_GameState* ret = SE_GameState__operatorequals(self, _ctor_arg);

    if (g_patch_ap_settings.patch_been_written_to) {
        if (!ap_gamestate_is_initialized()) {
            ap_init_gamestate();
        }
    } else {
        PRINTF("Cannot initialize gamestate! Patch not written by client.\n");
    }

    return ret;
}

bool TeleportPad_PlayerObjectives__GetObjective_PreCallHook(
    PlayerObjectives* self, EXHashCode hashcode, s32* result)
{
    // Realm teleporter is now always active
    *result = 1;
    return true;
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
    PRINTF("u8 keyring_bitfield[%d]: %x\n", AP_SETTINGS_KEYRINGS_BITFIELD_SIZE, &psettings->keyring_bitfield);
    PRINTF("u8 num_gem_packs_received: %x\n", &psettings->num_gem_packs_received);
    PRINTF("u8 num_lock_picks_received: %x\n", &psettings->num_lock_picks_received);
    PRINTF("u8 num_fire_ammo_received: %x\n", &psettings->num_fire_ammo_received);
    PRINTF("u8 num_electric_ammo_received: %x\n", &psettings->num_electric_ammo_received);
    PRINTF("u8 num_water_ammo_received: %x\n", &psettings->num_water_ammo_received);
    PRINTF("u8 num_ice_ammo_received: %x\n", &psettings->num_ice_ammo_received);
    PRINTF("u8 deathlink_ingoing: %x\n", &psettings->deathlink_ingoing);
    PRINTF("u8 deathlink_outgoing: %x\n", &psettings->deathlink_outgoing);
    PRINTF("bool infinite_butterfly_jar: %x\n", &psettings->infinite_butterfly_jar);
    PRINTF("bool randomize_shop: %x\n", &psettings->randomize_shop);
    PRINTF("bool use_key_rings: %x\n", &psettings->use_key_rings);
    PRINTF("bool skip_cutscene_button: %x\n", &psettings->skip_cutscene_button);
    PRINTF("bool allow_teleport_to_hub: %x\n", &psettings->allow_teleport_to_hub);
    PRINTF("bool disable_popups: %x\n", &psettings->disable_popups);
    PRINTF("bool instant_elevators: %x\n", &psettings->instant_elevators);
    PRINTF("bool starting_realm: %x\n", &psettings->starting_realm);
    PRINTF("bool[4] realm_access: %x\n", &psettings->realm_access);
    PRINTF("bool patch_been_written_to: %x\n", &psettings->patch_been_written_to);
    PRINTF("u32 mw_seed: %x\n", &psettings->mw_seed);
    PRINTF("u32 init: %x\n", &psettings->init);
    PRINTF("u8[4] boss_costs: %x\n", &psettings->boss_costs);
    PRINTF("u8[4] lg_door_costs: %x\n", &psettings->lg_door_costs);
    PRINTF("u8 invincibility_cost: %x\n", &psettings->invincibility_cost);
    PRINTF("u8 supercharge_cost: %x\n", &psettings->supercharge_cost);
    PRINTF("bool[4] boss_easy_mode: %x\n", &psettings->boss_easy_mode);
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

    // Safety measure. At this point, a death caused by deathlink is over,
    // and incoming deathlinks should be received.
    deathlink_ignore_next_death = false;

    return XSEItemHandler_Player__InitialiseStart(self);
}

void Player_urghhhImDead_PostHook()
{
    ap_handle_deathlink_outgoing(AP_DEATHLINK_REASON_DEFAULT);

    if (AP_GAMESTATE_SHOP_IS_RANDOMIZED)
    {
        return;
    }

    if (g_gamestate_ap_settings.infinite_butterfly_jar)
    {
        replenish_butterfly_jar = true;
    }
}

s32 SE_GameLoop__StartGameState_PreCallHook_BallGadgetDeath(SE_GameLoop *self, SE_GameState *pGS)
{
    ap_handle_deathlink_outgoing(AP_DEATHLINK_REASON_DEFAULT);

    return SE_GameLoop__StartGameState(self, pGS);
}

void SEMap_MiniGame__SetMiniGameDie_PreCallHook_SparxDeath(SE_Map* self)
{
    ap_handle_deathlink_outgoing(AP_DEATHLINK_REASON_DEFAULT);

    SEMap_MiniGame__SetMiniGameDie(self);
}

void SEMap_MiniGame__SetMiniGameFailed_PostHook()
{
    SE_Map* currmap = GetSpyroMap(0);

    switch (currmap->m_MapGeoHashCode) {
        case HT_File_MR1_Spy:
        case HT_File_MR2_Spy:
        case HT_File_MR3_Spy:
        case HT_File_MR4_Spy:
            ap_handle_deathlink_outgoing(AP_DEATHLINK_REASON_DEFAULT);
            break;
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
