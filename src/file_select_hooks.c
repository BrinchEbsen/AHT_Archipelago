#include <file_select_hooks.h>
#include <ap_settings.h>
#include <ap_patch.h>
#include <paneldraw.h>

void MemCardSlotMenu__DrawSavedGameInfo_PreCallHook(GUI_Base* self, void* pWnd, SavedGame* pSavedGame)
{
    if (!g_patch_ap_settings.patch_been_written_to) {
        textprint(pWnd, 200, 0, 1.0f, Centre, COLOR_WHITE, false,
            "WARNING!\nSettings not initialized!\nConnect Archipelago client.");
        return;
    }

    if (MEMCARDSLOTMENU_M_LOADGAMEFLAG(self) != 0) {
        APSettings* p_settings = OFFSET_PTR(APSettings, &pSavedGame->m_GameState.m_BitHeap, 0x2000);
        if (g_patch_ap_settings.mw_seed != p_settings->mw_seed) {
            textprintf(pWnd, 200, 0, 1.0f, Centre, COLOR_WHITE, false,
                "WARNING!\nSeed mismatch!\nLoad another save or start a new one.\nCurrent multiworld seed: %x\nFile seed: %x",
            g_patch_ap_settings.mw_seed, p_settings->mw_seed);
            return;
        }
    }
    
    MemCardSlotMenu__DrawSavedGameInfo(self, pWnd, pSavedGame);
}
