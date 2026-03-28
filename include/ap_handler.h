#ifndef AP_HANDLER_H
#define AP_HANDLER_H
#include <types.h>
#include <gameflow.h>
#include <gamestate.h>
#include <ap_settings.h>
#include <gameloop.h>

typedef enum CostTextType
{
    COST_LightGem,
    COST_DarkGem
} CostTextType;

extern bool draw_cost_text;
extern CostTextType cost_text_type;
extern int cost_text_amt;

static inline bool ap_gamestate_is_initialized() {
    return g_gamestate_ap_settings.init == AP_SETTINGS_INIT_MAGICVALUE;
}

static inline void ap_set_gamestate_initialized() {
    g_gamestate_ap_settings.init = AP_SETTINGS_INIT_MAGICVALUE;
}

// runs every frame
void ap_update();

void ap_gamestate_update();

void dbg_add_shop_item();

void dbg_remove_shop_item();

void ap_draw(void* pWnd);

void ap_draw_cost_text(void* pWnd, CostTextType type, int amt);

void ap_init_gamestate();

void ap_update_realm_access();

SE_GameState* mapchanger_SE_GameState__operatorequals_PreCallHook(SE_GameState* self, SE_GameState* _ctor_arg);

bool TeleportPad_PlayerObjectives__GetObjective_PreCallHook(
    PlayerObjectives* self, EXHashCode hashcode, s32* result);

// int ap_binary_search_grabbable(u16 map_index, u16 trigger_index);

void print_interface_addresses();

void print_apsettings_addresses(APSettings* psettings);

int XSEItemHandler_Player__InitialiseStart_PreCallHook(void* self);

void Player_urghhhImDead_PostHook();

s32 SE_GameLoop__StartGameState_PreCallHook_BallGadgetDeath(SE_GameLoop* self, SE_GameState* pGS);

void SEMap_MiniGame__SetMiniGameDie_PreCallHook_SparxDeath(SE_Map* self);

void SEMap_MiniGame__SetMiniGameFailed_PostHook();

extern int Popup__Update(void* self);
int Popup__Update_VtableHook(void* self);

s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow* self);

#endif /* AP_HANDLER_H */