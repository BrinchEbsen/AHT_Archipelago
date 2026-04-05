#ifndef FILE_SELECT_HOOKS_H
#define FILE_SELECT_HOOKS_H
#include <gui_base.h>
#include <savedgame.h>

#define MEMCARDSLOTMENU_M_LOADGAMEFLAG(self) OFFSET_VAL(s32, self, 0x1C0)
#define TITLELOOP_M_STATE(self) OFFSET_VAL(int, self, 0x3ac)

extern void MemCardSlotMenu__DrawSavedGameInfo(GUI_Base* self, void* pWnd, SavedGame* pSavedGame);
extern s32 MemCardSlotMenu__v_OnSelect(GUI_Base* self, void* pMenuItem);
extern s32 TitleLoop__v_DrawStateRunning(GUI_Base* self, void* pWnd);

void MemCardSlotMenu__DrawSavedGameInfo_PreCallHook(GUI_Base* self, void* pWnd, SavedGame* pSavedGame);
s32 MemCardSlotMenu__v_OnSelect_VtableHook(GUI_Base* self, void* pMenuItem);
s32 TitleLoop__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd);

bool test_save_select_warning(GUI_Base* self, void* pWnd, SavedGame* pSavedGame);

#endif /* FILE_SELECT_HOOKS_H */