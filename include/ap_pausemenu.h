#ifndef AP_PAUSEMENU_H
#define AP_PAUSEMENU_H
#include <types.h>
#include <gui_base.h>
#include <gameloop.h>

// Whether the shop from the pause menu is opening.
extern bool instant_shop_opening;
// The text string representing the reason the shop cannot open.
// Will be NULL if the shop can open.
extern char* instant_shop_cannot_open_reason;

typedef enum PauseMenuPage
{
    PauseMenu_Abilities,
    PauseMenu_Keyrings,
    PauseMenu_Realms,
    PauseMenu_NUM
} PauseMenuPage;

typedef void(*SE_Loop__RequestClose_func)(SE_Loop*, s32);

#define GUI_MENU__M_MENUFLAGS(self) OFFSET_VAL(u32, self, 0x1a0)

extern GUI_Base* gpPanelShop;
void PanelShop__OpenShop(GUI_Base* self, Bool shopViaTeleporter);

extern s32 GUI_PauseMenu__v_DrawStateRunning(GUI_Base* self, void* pWnd);
s32 GUI_PauseMenu__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd);

extern s32 GUI_PauseMenu__v_StateRunning(GUI_Base* self);
s32 GUI_PauseMenu__v_StateRunning_VtableHook(GUI_Base* self);

/// @brief Whether the player should be able to open the shop from the pause menu.
/// @param reason The string containing the reason for not being able to open the shop.
/// This is set to NULL if the shop can be opened.
/// @return Whether the shop can be opened.
bool can_start_shop_sequence(char** reason);

// Logic for while the shop is opening.
void handle_instant_shop_sequence();

// Handle controls for pause menu.
bool do_pause_menu_controls();

// Draw the "teleport to HUB" or "open shop" text at the bottom.
void draw_teleport_menu(GUI_Base* self, void* pWnd);

// Draw the shop opening option at the bottom.
void draw_instant_shop_menu(GUI_Base* self, void* pWnd);

// Draw the currently selected stats page on the left.
void draw_pause_stats(GUI_Base* self, void* pWnd);

// Draw the stats page with the ability flags.
void draw_stats_abilities(GUI_Base* self, void* pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col);

// Draw the stats page with the keyrings.
void draw_stats_keyrings(GUI_Base* self, void* pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col);

// Draw the stats page with the accessible realms.
void draw_stats_realms(GUI_Base* self, void* pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col);

// Draw the notification toggle button prompt.
void draw_notification_toggle(GUI_Base* self, void* pWnd);

// Draw the map icon toggle button prompt.
void draw_ut_stats(GUI_Base* self, void* pWnd);

// Draw the stats for the gem logic.
void draw_gem_stats(GUI_Base* self, void* pWnd);

// Request for the pause menu to close.
void close_pause_menu(GUI_Base* self);

// Teleport the player to the HUB of the current realm.
void teleport_to_hub();

extern s32 SE_GameLoop__Teleport(SE_GameLoop* self, SE_GameState* pGS);
s32 SE_GameLoop__Teleport_PreCallHook(SE_GameLoop* self, SE_GameState* pGS);

// Reset the progress of bosses if they haven't been beaten yet.
// This is done when teleporting to prevent softlocks due to buggy behavior when escaping
// and re-entering bosses.
void reset_boss_progress();

#endif /* AP_PAUSEMENU_H */