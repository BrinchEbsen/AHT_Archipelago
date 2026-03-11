#ifndef FILE_SELECT_HOOKS_H
#define FILE_SELECT_HOOKS_H
#include <gui_base.h>
#include <savedgame.h>

#define MEMCARDSLOTMENU_M_LOADGAMEFLAG(self) OFFSET_VAL(s32, self, 0x1C0)

extern void MemCardSlotMenu__DrawSavedGameInfo(GUI_Base* self, void* pWnd, SavedGame* pSavedGame);

void MemCardSlotMenu__DrawSavedGameInfo_PreCallHook(GUI_Base* self, void* pWnd, SavedGame* pSavedGame);

#endif /* FILE_SELECT_HOOKS_H */