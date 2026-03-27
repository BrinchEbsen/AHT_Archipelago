#ifndef AP_PAUSEMENU_H
#define AP_PAUSEMENU_H
#include <types.h>
#include <gui_base.h>

typedef enum PauseMenuPage
{
    PauseMenu_Abilities,
    PauseMenu_Keyrings,
    PauseMenu_NUM
} PauseMenuPage;

typedef void(*SE_Loop__RequestClose_func)(SE_Loop*, s32);

#define GUI_MENU__M_MENUFLAGS(self) OFFSET_VAL(u32, self, 0x1a0)

extern s32 GUI_PauseMenu__v_DrawStateRunning(GUI_Base* self, void* pWnd);
s32 GUI_PauseMenu__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd);

extern s32 GUI_PauseMenu__v_StateRunning(GUI_Base* self);
s32 GUI_PauseMenu__v_StateRunning_VtableHook(GUI_Base* self);

bool do_pause_menu_controls();

void draw_teleport_menu(GUI_Base* self, void* pWnd);

void draw_pause_stats(GUI_Base* self, void* pWnd);

void draw_stats_abilities(GUI_Base* self, void* pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col);

void draw_stats_keyrings(GUI_Base* self, void* pWnd, u16 x, u16 y, u16 spacing, RGBA on_col, RGBA off_col);

void draw_notification_toggle(GUI_Base* self, void* pWnd);

void close_pause_menu(GUI_Base* self);

void teleport_to_hub();

#endif /* AP_PAUSEMENU_H */