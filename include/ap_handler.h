#ifndef AP_HANDLER_H
#define AP_HANDLER_H
#include <types.h>
#include <gameflow.h>
#include <gamestate.h>
#include <ap_settings.h>
#include <gameloop.h>

/*
 * Fair warning, ap_handler is kind of a misnomer. It's mostly just a place i dump
 * various bits of code i didn't bother making a dedicated translation unit for.
 */

typedef enum CostTextType
{
    COST_LightGem,
    COST_DarkGem
} CostTextType;

// Draw the light/dark gem cost on-screen this frame.
extern bool draw_cost_text;
// Type of cost to draw.
extern CostTextType cost_text_type;
// The amount of light/dark gems to display on the cost text.
extern int cost_text_amt;

// Whether to draw the "Y to skip" text this frame.
extern bool draw_cutscene_skip_text;

static inline bool ap_gamestate_is_initialized() {
    return g_gamestate_ap_settings.init == AP_SETTINGS_INIT_MAGICVALUE;
}

static inline void ap_set_gamestate_initialized() {
    g_gamestate_ap_settings.init = AP_SETTINGS_INIT_MAGICVALUE;
}

// Main update, runs every frame.
void ap_update();

// Update routine for the game's state.
void ap_gamestate_update();

void dbg_add_shop_item();

void dbg_remove_shop_item();

// Hooks into the drawing routine for drawing text, icons, etc.
void ap_draw(void* pWnd);

// Draw a message with a cost of either dark gems or light gems.
void ap_draw_cost_text(void* pWnd, CostTextType type, int amt);

// Copy the settings from the patch area and set up the current save's state.
void ap_init_gamestate();

// Update which levels the player has access to.
void ap_update_realm_access();

// Assembly patches for being able to teleport across realms with the shop pad.
void ap_update_teleport_anywhere();

extern int XSEItemHandler_StartPoint__Update(void* self);
// Hook into the StartPoint object's update routine to disable its handling of
// the "visited" flag that determines if a shop pad activates when you get close
// to it.
int XSEItemHandler_StartPoint__Update_VtableHook(void* self);

// Replace the callback for checking if a shop pad is selectable,
// to disable the behavior where main shops are always selectable.
s32 GUI_MiniMap__Callback_IsRestartSelectable_ReImplHook(GameStateTrigInfo* pTrigInfo, u32 Val);

// Hook into the final copying of the save's gamestate into the current gamestate.
// This lets us initialize it with AP stuff before the save is started for real.
SE_GameState* mapchanger_SE_GameState__operatorequals_PreCallHook(SE_GameState* self, SE_GameState* _ctor_arg);

// Replace the teleport pad's call to check if the first boss has been
// beaten yet, to instead force it to always be active.
bool TeleportPad_PlayerObjectives__GetObjective_PreCallHook(
    PlayerObjectives* self, EXHashCode hashcode, s32* result);

// Print out addresses for the client to Dolphin's log window.
void print_interface_addresses();

// Helper function for printing addresses of an AP settings struct.
void print_apsettings_addresses(APSettings* psettings);

// Called whenever the player is initialized.
int XSEItemHandler_Player__InitialiseStart_PreCallHook(void* self);

// Get the ID of the death that just occured.
// To be called the moment the player has died and the game is restarting.
DeathLinkReason get_deathlink_reason();

// Runs right after the player has died.
void Player_urghhhImDead_PostHook();

// Runs right as the game is reloading from a ball gadget death.
s32 SE_GameLoop__StartGameState_PreCallHook_BallGadgetDeath(SE_GameLoop* self, SE_GameState* pGS);

// Runs right as the game is reloading from a Sparx minigame death.
void SEMap_MiniGame__SetMiniGameDie_PreCallHook_SparxDeath(SE_Map* self);

// Runs right after a minigame has been failed.
void SEMap_MiniGame__SetMiniGameFailed_PostHook();

extern int Popup__Update(void* self);
// Hook into the Popup-object's update routine.
int Popup__Update_VtableHook(void* self);

// Generic every-frame hook for running whatever code we need.
s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow* self);

#endif /* AP_HANDLER_H */