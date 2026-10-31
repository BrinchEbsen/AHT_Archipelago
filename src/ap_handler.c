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
#include <boss_hooks.h>
#include <ap_version.h>
#include <ap_triginfo.h>
#include <ap_pausemenu.h>
#include <ap_trap.h>
#include <ap_warps.h>
#include <mapindex.h>
#include <ap_keys.h>

#if AP_DEBUG_ADD_REMOVE_SHOP_ITEMS!=0
void dbg_add_shop_item();
void dbg_remove_shop_item();
#endif

#if AP_DEBUG_SCRAMBLE_BITFIELDS!=0
#include <exrand.h>
#endif

MapOrderInfo realm_teleporter_maporderinfo[] = {
    { .m_FileHash = HT_File_Realm1A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm2A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm3A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm4A,    .m_MapHash = 0xFFFFFFFF }
};

s32 realm_hub_map_indexes[] = {
    MI_DragonVillage,
    MI_CoastalRemains,
    MI_FrostbiteVillage,
    MI_StormyBeach
};

bool replenish_butterfly_jar = false;

bool draw_cost_text = false;
CostTextType cost_text_type = LightGem;
int cost_text_amt = 0;

bool draw_cutscene_skip_text = false;

bool do_autosave = false;

bool has_opened_minimap = false;

void ap_update()
{
    if (g_patch_ap_settings.patch_been_written_to && (gGameLoop.m_State == Running)) {
        ap_gamestate_update();
    }
}

void ap_gamestate_update()
{
    if (!ap_gamestate_is_initialized()) {
        return;
    }

    if (do_autosave) {
        if (!gGameLoop.m_GameIsPaused && (gpPlayer != NULL)) {
            MemCard_AutoSave();
            do_autosave = false;
        }
    }

    if (g_gamestate_ap_settings.infinite_double_gem)
    {
        gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_DOUBLE_GEM;
        static float freeze = 60.0f * 60.0f * 60.0f; // 1 hour
        gGameState.m_PlayerState.m_DoubleGemTimerMax = freeze;
        gGameState.m_PlayerState.m_DoubleGemTimer = freeze;
    }

    if (AP_GAMESTATE_SHOP_IS_RANDOMIZED)
    {
        // Freeze max values for lock picks and breath ammo
        if (g_gamestate_ap_settings.key_mode == KeyMode_VanillaLockpicks) {
            gGameState.m_PlayerState.m_LockPickers_Max = 127;
        }
        gGameState.m_PlayerState.m_FlameBombs_Max = 127;
        gGameState.m_PlayerState.m_IceBombs_Max = 127;
        gGameState.m_PlayerState.m_WaterBombs_Max = 127;
        gGameState.m_PlayerState.m_ElectricBombs_Max = 127;
    }

    if (g_gamestate_ap_settings.key_mode == KeyMode_KeyRings) {
        // Lock picks are essentially disabled when using key rings.
        gGameState.m_PlayerState.m_LockPickers = 0;
        gGameState.m_PlayerState.m_LockPickers_Max = 0;
    }
    else if (g_gamestate_ap_settings.key_mode == KeyMode_PerLevelLockpicks) {
        // The amount and maximum of the lock pick count is set to that of the current level.

        SE_Map* map = GetSpyroMap(0);
        int keys_index = ap_keys_get_level_index(map);

        if (keys_index < 0)
        {
            gGameState.m_PlayerState.m_LockPickers = 0;
            gGameState.m_PlayerState.m_LockPickers_Max = 0;
        }
        else
        {
            gGameState.m_PlayerState.m_LockPickers = g_gamestate_ap_settings.perlevel_lockpicks[keys_index].num;
            gGameState.m_PlayerState.m_LockPickers_Max = g_ap_keys_num_chests[keys_index];
        }
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

    if (gGameState.m_PlayerState.m_TotalLightGems >= g_gamestate_ap_settings.ball_gadget_cost) {
        PlayerObjectives__SetObjective__ReImplHook(&gGameState.m_PlayerObjectives, HT_Objective_BallGadgetPowered);
    } else {
        PlayerObjectives__ClearObjective(&gGameState.m_PlayerObjectives, HT_Objective_BallGadgetPowered);
    }
    
    ap_deathlink_update();

    ap_trap_update();

    ap_update_realm_access();

    ap_setup_boss_damage();

    ap_update_teleport_anywhere();

    ap_warps_update();

    if (instant_shop_opening)
    {
        handle_instant_shop_sequence();
    }

    #if AP_DEBUG_DEATHLINK!=0
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

    #if AP_DEBUG_ADD_REMOVE_SHOP_ITEMS!=0
    if (g_pad_button_state(PAD_BUTTON_B)) {
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_RIGHT)) {
            dbg_add_shop_item();
        } else if (g_pad_button_edge_down(PAD_BUTTON_DPAD_LEFT)) {
            dbg_remove_shop_item();
        }
    }
    #endif

    #if AP_DEBUG_NOTIFICATION!=0
    if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
        ap_set_notification(60*5, COLOR_WHITE,
            u"Test notification! The notification that tests things! Something testy happened, probably!");
    }
    #endif

    #if AP_DEBUG_SCRAMBLE_BITFIELDS!=0
    if (g_pad_button_state(PAD_BUTTON_B)) {
        if (g_pad_button_edge_down(PAD_BUTTON_DPAD_DOWN)) {
            for (int i = 0; i < AP_SETTINGS_LOCATIONS_BITFIELD_SIZE; i++)
            {
                u32 r = RAND32;
                g_gamestate_ap_settings.location_bitfield_collected[i] = r & 0xFF;
                g_gamestate_ap_settings.location_bitfield_reachable[i] = (r & 0xFF00) >> 8;
                g_gamestate_ap_settings.location_bitfield_reachable_trick[i] = (r & 0xFF0000) >> 16;
            }
        }
    }
    #endif
}

#if AP_DEBUG_ADD_REMOVE_SHOP_ITEMS!=0
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
    wchar16* shoptext = g_gamestate_ap_settings.shop_text[index-1].text;
    
    char buff[48];
    sprintf(buff, "Example check item %d", index);

    Wcscpy(shoptext, buff);
    
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

        if (draw_cutscene_skip_text)
        {
            draw_cutscene_skip_text = false;
            TEXT_PRINT_COLOR(pWnd, 0, 0, COLOR_WHITE, "~X Skip");
        }

        if (draw_warp_text)
        {
            TEXT_PRINT_ALIGN(pWnd, 0, 0, Centre, "~Y to warp across");
        }

        #if AP_DEBUG_DEATHLINK!=0
        TEXT_PRINT_ALIGN_COLOR_F(pWnd, 0, 0, CentreLeft, COLOR_LIGHT_RED,
            "DL in: %d\nDL out: %d\nign: %d",
            g_gamestate_ap_settings.deathlink_ingoing,
            g_gamestate_ap_settings.deathlink_outgoing,
            deathlink_ignore_next_death);
        #endif

        // TEXT_PRINT_ALIGN_F(pWnd, 0, 0, CentreLeft, "G: %d\nT: %d",
        //     gGameState.m_PlayerState.m_Gems, gGameState.m_PlayerState.m_TotalGems);
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

    #if AP_DEBUG_QUICK_START!=0
    gGameState.m_PlayerState.m_AbilityFlags |= (
        ABILITY_AP_FIREBREATH |
        ABILITY_AP_GLIDE |
        ABILITY_AP_CHARGE |
        ABILITY_AP_SWIM |
        ABILITY_DOUBLE_JUMP |
        ABILITY_ELECTRIC_BREATH |
        ABILITY_WATER_BREATH |
        ABILITY_ICE_BREATH
    );
    #endif

    if (g_gamestate_ap_settings.starting_realm > 3) {
        g_gamestate_ap_settings.starting_realm = 0;
    }

    gGameState.m_StartMapIndex = realm_hub_map_indexes[g_gamestate_ap_settings.starting_realm];

    MiniMapStatus__SetBitName(
        &gMiniMapStatus,
        &realm_teleporter_maporderinfo[g_gamestate_ap_settings.starting_realm],
        Selectable);

    // Set starting game objectives
    for (int i = 0; i < NUM_NEW_GAME_OBJECTIVES; i++) {
        PlayerObjectives__SetObjective__ReImplHook(
            &gGameState.m_PlayerObjectives,
            HT_Objective_HASHCODE_BASE | new_game_objectives[i]);
    }

    // Set objective flag for having bought a lock pick
    gGameState.m_PlayerState.m_AbilityFlags |= ABILITY_BOUGHT_LOCK_PICK;

    if (g_gamestate_ap_settings.unlock_all_shops) {
        for (int i = 0; i < NUM_SHOP_TRIGINFOS; i++) {
            set_u8_bitfield_value(g_gamestate_ap_settings.shoppad_bitfield, i, 1);
        }
    }

    do_autosave = true;

    ap_set_gamestate_initialized();
}

void ap_update_realm_access()
{
    // Update which realm HUB's are selectable in the realm teleporter.
    for (int i = 0; i < 4; i++) {
        if (g_gamestate_ap_settings.realm_access[i]) {
            MiniMapStatus__SetBitName(
                &gMiniMapStatus,
                &realm_teleporter_maporderinfo[i],
                Selectable);
        }
    }

    // Update which shop pads are selectable.
    for (int i = 0; i < NUM_SHOP_TRIGINFOS; i++)
    {
        // Try to enable the shop pad if its bit is set
        if (get_u8_bitfield_value(g_gamestate_ap_settings.shoppad_bitfield, i))
        {
            s32 existing_index = SE_GameState__FindTrigInfo(
                &gGameState,
                shops_triginfos[i].m_MapIndex,
                shops_triginfos[i].m_TrigIndex);

            // If shop pad isn't in the list, add it to the list.
            if (existing_index == -1)
            {
                memcpy(&gGameState.m_TrigInfo[gGameState.m_NumTrigInfo], &shops_triginfos[i], sizeof(GameStateTrigInfo));
                gGameState.m_NumTrigInfo++;
            } else {
                // If it is in the list, mark it as visited.
                gGameState.m_TrigInfo[existing_index].u.RestartPoint.HasVisited = 1;
            }

            // Set the pad's map as visible.
            // It's probably inefficient since it'll inevitably set the same map
            // multiple times during the loop, but whatevs ¯\_(ツ)_/¯
            MiniMapStatus__SetBitName(
                &gMiniMapStatus,
                &shops_mapinfos[shop_triginfo_mapinfo_indexes[i]],
                Visible);
        }
    }
}

void ap_update_teleport_anywhere() {
    if (!g_gamestate_ap_settings.teleport_anywhere) {
#if defined(GC_NTSC)
        // PrevSelectableRestart - Only if RealmID matches current
        *((u32*)0x801aecac) = 0x7c7f1b78; // mr r31, r3
        // NextSelectableRestart - Only if RealmID matches current
        *((u32*)0x801aeb8c) = 0x7c7f1b78; // mr r31, r3
        // GetNumBuyableShopPads - Get map realm to compare with
        *((u32*)0x801af128) = 0x801f008c; // lwz r0, 0x008C (r31)
#elif defined(GC_PAL)
        // PrevSelectableRestart - Only if RealmID matches current
        *((u32*)0x801af2c4) = 0x7c7f1b78; // mr r31, r3
        // NextSelectableRestart - Only if RealmID matches current
        *((u32*)0x801af1a4) = 0x7c7f1b78; // mr r31, r3
        // GetNumBuyableShopPads - Get map realm to compare with
        *((u32*)0x801af740) = 0x801f008c; // lwz r0, 0x008C (r31)
#endif
    } else {
#if defined(GC_NTSC)
        // PrevSelectableRestart - Assume RealmID matches
        *((u32*)0x801aecac) = 0x3be00001; // li r31, 1
        // NextSelectableRestart - Assume RealmID matches
        *((u32*)0x801aeb8c) = 0x3be00001; // li r31, 1
        // GetNumBuyableShopPads - Assume RealmID matches
        *((u32*)0x801af128) = 0x7f20cb78; // mr r0, r25
#elif defined(GC_PAL)
        // PrevSelectableRestart - Assume RealmID matches
        *((u32*)0x801af2c4) = 0x3be00001; // li r31, 1
        // NextSelectableRestart - Assume RealmID matches
        *((u32*)0x801af1a4) = 0x3be00001; // li r31, 1
        // GetNumBuyableShopPads - Assume RealmID matches
        *((u32*)0x801af740) = 0x7f20cb78; // mr r0, r25
#endif
    }
}

int XSEItemHandler_StartPoint__Update_VtableHook(void* self)
{
    if (g_gamestate_ap_settings.disable_shop_pad_proximity_activate)
    {
        // Force the first of the flags in m_Flags to 0.
        // Disables the handling of the "visited" triginfo flag.
        OFFSET_VAL(u32, self, 0x3DC) &= ~1u;
    }

    return XSEItemHandler_StartPoint__Update(self);
}

s32 GUI_MiniMap__Callback_IsRestartSelectable_ReImplHook(GameStateTrigInfo* pTrigInfo, u32 Val)
{
    EXHashCode restart_hash = pTrigInfo->u.RestartPoint.HashCode;
    bool has_visited = pTrigInfo->u.RestartPoint.HasVisited != 0;
    bool is_shop = restart_hash == HT_StartPoint_SHOP;
    bool is_main_shop = restart_hash == HT_StartPoint_MAINSHOP;
    bool disable_vanilla = g_gamestate_ap_settings.disable_main_shop_always_available;

    // If it's not a shop
    if (!is_shop && !is_main_shop)
    {
        return 0;
    }

    // If it's a remote shop, but not visited
    if (is_shop && !has_visited)
    {
        return 0;
    }

    // If the vanilla behavior is disabled, we'll also deem a main shop
    // unselectable if it hasn't been visited.
    // Otherwise, just always let it be selectable.
    if (disable_vanilla && is_main_shop && !has_visited)
    {
        return 0;
    }

    return pTrigInfo->m_TrigIndex != gMiniMapStatus.m_CurrentShopRestart;
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

int XSEItemHandler_Player__InitialiseStart_PreCallHook(void* self)
{
    // Replenish the player's butterfly jar if it was requested.
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

DeathLinkReason get_deathlink_reason()
{
    if (gpPlayer == NULL) return DLReason_Default;

    Players playerType = XSEItemHandler_Player__M_PLAYERTYPE(gpPlayer);
    PlayerModes mode = XSEItemHandler_Player__M_PLAYERMODE(gpPlayer);
    EXHashCode animmode = OFFSET_VAL(PlayerModes, OFFSET_VAL(void*, gpPlayer, 0), 0x180);

    // Combine the playermode and animmode for easier checking.
    u32 combine = (mode << 16) | (animmode & 0xFFFF);

    switch (playerType)
    {
        case Player_Spyro:
            switch (combine)
            {
                case (water_death   << 16) | (HT_AnimMode_Swim_Death    & 0xFFFF): return DLReason_Spy_Water;
                case (deathfall     << 16) | (HT_AnimMode_FallLong      & 0xFFFF): return DLReason_Spy_Fall;
                case (swamp_death   << 16) | (HT_AnimMode_Idle          & 0xFFFF): return DLReason_Spy_Lava;
                case (nomode        << 16) | (HT_AnimMode_SwampDeath    & 0xFFFF): return DLReason_Spy_Swamp;
                case (squashed      << 16) | (HT_AnimMode_Victory       & 0xFFFF): return DLReason_Spy_Squash;
                case (iceydeath     << 16) | (HT_AnimMode_IceLand       & 0xFFFF): return DLReason_Spy_Freeze;
                default: return DLReason_Spy_Default;
            }

        case Player_Hunter:
            switch (combine)
            {
                case (deathfall     << 16) | (HT_AnimMode_DeathFall     & 0xFFFF): return DLReason_Hun_Fall;
                case (swamp_death   << 16) | (HT_AnimMode_SwampDeath    & 0xFFFF): return DLReason_Hun_Drown;
                case (squashed      << 16) | (HT_AnimMode_Victory       & 0xFFFF): return DLReason_Hun_Squash;
                default: return DLReason_Hun_Default;
            }

        case Player_Blinky:
            switch (combine)
            {
                case (deathfall     << 16) | (HT_AnimMode_DeathFall     & 0xFFFF): return DLReason_Blk_Fall;
                case (swamp_death   << 16) | (HT_AnimMode_LavaLand      & 0xFFFF): return DLReason_Blk_Lava;
                case (drown         << 16) | (HT_AnimMode_Wasp_Die      & 0xFFFF): return DLReason_Blk_Drown;
                case (squashed      << 16) | (HT_AnimMode_Victory       & 0xFFFF): return DLReason_Blk_Squash;
                default: return DLReason_Blk_Default;
            }

        case Player_SrgBird:
            switch (combine)
            {
                case (water_dive    << 16) | (HT_AnimMode_CrashLand     & 0xFFFF): return DLReason_Sgt_WaterCrash;
                case (breatheFire   << 16) | (HT_AnimMode_Fly           & 0xFFFF): return DLReason_Sgt_LavaCrash;
                case (deathfall     << 16) | (HT_AnimMode_Fall          & 0xFFFF): return DLReason_Sgt_Fall;
                default: return DLReason_Sgt_Default;
            }

        default: return DLReason_Default;
    }
}

void Player_urghhhImDead_PostHook()
{
    DeathLinkReason reason = get_deathlink_reason();
    ap_handle_deathlink_outgoing(reason);

    if (!AP_GAMESTATE_SHOP_IS_RANDOMIZED)
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
    ap_handle_deathlink_outgoing(DLReason_Ball_Default);

    return SE_GameLoop__StartGameState(self, pGS);
}

void SEMap_MiniGame__SetMiniGameDie_PreCallHook_SparxDeath(SE_Map* self)
{
    ap_handle_deathlink_outgoing(DLReason_Spx_Default);

    SEMap_MiniGame__SetMiniGameDie(self);
}

void SEMap_MiniGame__SetMiniGameFailed_PostHook()
{
    SE_Map* currmap = GetSpyroMap(0);

    // Send the correct deathlink if we're in a turret level.
    switch (currmap->m_MapGeoHashCode) {
        case HT_File_MR1_Spy:
            ap_handle_deathlink_outgoing(DLReason_Turret_R1);
            break;
        case HT_File_MR2_Spy:
            ap_handle_deathlink_outgoing(DLReason_Turret_R2);
            break;
        case HT_File_MR3_Spy:
            ap_handle_deathlink_outgoing(DLReason_Turret_R3);
            break;
        case HT_File_MR4_Spy:
            ap_handle_deathlink_outgoing(DLReason_Turret_R4);
            break;
    }
}

int Popup__Update_VtableHook(void* self)
{
    // Return -1 (Kill) as the update response if we're disabling popups.
    if (g_gamestate_ap_settings.disable_popups)
    {
        return -1;
    }

    return Popup__Update(self);
}

// (yes they spelt "Lilypad" wrong)
int LillyPad__Update_VtableHook(void* self)
{
    // Make lilypads by Fredneck rise on their own if turret minigames are disabled.
    if (g_gamestate_ap_settings.minigame_turret_config == MinigameConfig_Disabled)
    {
        // Only rise if the nearby dark gem is destroyed.
        s32 obj;
        PlayerObjectives__GetObjective__ReImplHook(
            &gGameState.m_PlayerObjectives, HT_Objective_DX_1B_02, &obj);
        
        if (obj)
        {
            OFFSET_VAL(u16, self, 0x3e2) |= 1;
        }
    }

    return LillyPad__Update(self);
}

float get_checks_percentage()
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

        bool easyonly = false;
        bool disabled = false;

        if (get_minigame_collectable_config(coll, &easyonly, &disabled))
        {
            if (disabled)
            {
                continue;
            }
            if ((coll->type == LightGem_MiniGame) && easyonly)
            {
                continue;
            }
        }

        total++;
        collected += get_u8_bitfield_value(g_gamestate_ap_settings.location_bitfield_collected, i);
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

    return ((float)collected / (float)total) * 100.0f;
}

void LoadingLoop2D__XWnd__TextPrint_PreCallHook(void* self, EXHashCode Code)
{
    char* tiptext = has_opened_minimap ? "" : "\nHold ~S to open the minimap screen!";

    float percentage = get_checks_percentage();

    sprintf(gVarTextBuffer, "Checks: %.1f%%%s", percentage, tiptext);

    XWnd__TextPrintC(self, gVarTextBuffer);
}

s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow *self)
{
    // Get or create a GUI element to assign a draw-routine.
    if (gp_paneldraw_loop == NULL) {
        GUI_Base* paneldraw = paneldraw_create();
        if (paneldraw != NULL) {
            paneldraw_callback = ap_draw;
        }
    }

    // Every frame update.
    ap_update();

    return SEGameFlow__v_StateRunning(self);
}
