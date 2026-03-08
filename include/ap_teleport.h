#ifndef AP_TELEPORT_H
#define AP_TELEPORT_H
#include <types.h>
#include <gui_base.h>

typedef void(*SE_Loop__RequestClose_func)(SE_Loop*, s32);

#define GUI_MENU__M_MENUFLAGS(self) OFFSET_VAL(u32, self, 0x1a0)

extern s32 GUI_PauseMenu__v_DrawStateRunning(GUI_Base* self, void* pWnd);
s32 GUI_PauseMenu__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd);

extern s32 GUI_PauseMenu__v_StateRunning(GUI_Base* self);
s32 GUI_PauseMenu__v_StateRunning_VtableHook(GUI_Base* self);

void draw_teleport_menu(GUI_Base* self, void* pWnd);

void close_pause_menu(GUI_Base* self);

void teleport_to_hub();

#endif /* AP_TELEPORT_H */