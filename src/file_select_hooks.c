#include <file_select_hooks.h>
#include <ap_settings.h>
#include <ap_patch.h>
#include <paneldraw.h>
#include <pad.h>

bool ap_save_warning_active = false;

void MemCardSlotMenu__DrawSavedGameInfo_PreCallHook(GUI_Base* self, void* pWnd, SavedGame* pSavedGame)
{
    if (test_save_select_warning(self, pWnd, pSavedGame)) {
        ap_save_warning_active = true;
        return;
    } else {
        ap_save_warning_active = false;
    }
    
    MemCardSlotMenu__DrawSavedGameInfo(self, pWnd, pSavedGame);
}

s32 MemCardSlotMenu__v_OnSelect_VtableHook(GUI_Base* self, void* pMenuItem)
{
    if (ap_save_warning_active && !g_pad_button_state(PAD_BUTTON_R)) {
        return 0;
    }

    return MemCardSlotMenu__v_OnSelect(self, pMenuItem);
}

s32 TitleLoop__v_DrawStateRunning_VtableHook(GUI_Base* self, void* pWnd)
{
    switch (TITLELOOP_M_STATE(self)) {
        case 1: // TitleState_PressStart
        case 2: // TitleState_StartMenu
        case 4: // TitleState_ExtrasMenu
            TEXT_PRINT_COLOR(pWnd, 0, 0, COLOR_WHITE, "Archipelago v1.0.1");
            if (g_patch_ap_settings.patch_been_written_to) {
                TEXT_PRINT_COLOR(pWnd, 0, 20, COLOR_LIGHT_GREEN, "Settings initialized");
            } else {
                TEXT_PRINT_COLOR(pWnd, 0, 20, COLOR_LIGHT_RED, "Settings not initalized - Connect client");
            }
            break;
    }

    return TitleLoop__v_DrawStateRunning(self, pWnd);
}

bool test_save_select_warning(GUI_Base* self, void* pWnd, SavedGame* pSavedGame)
{
    if (!g_patch_ap_settings.patch_been_written_to) {
        textprint(pWnd, 200, 0, 1.0f, Centre, COLOR_WHITE, false,
            "WARNING!\nSettings not initialized!\nConnect Archipelago client.\n~R+~A to force-select.");
        return true;
    }

    if (MEMCARDSLOTMENU_M_LOADGAMEFLAG(self) != 0) {
        APSettings* p_settings = OFFSET_PTR(APSettings, &pSavedGame->m_GameState.m_BitHeap, 0x2000);

        if (p_settings->init != AP_SETTINGS_INIT_MAGICVALUE) {
            textprintf(pWnd, 200, 0, 1.0f, Centre, COLOR_WHITE, false,
                "WARNING!\nThis save was not started with archipelago.\nLoad another save or start a new one.\n~R+~A to force-select.");
            return true;
        }

        if (g_patch_ap_settings.mw_seed != p_settings->mw_seed) {
            textprintf(pWnd, 200, 0, 1.0f, Centre, COLOR_WHITE, false,
                "WARNING!\nSeed mismatch!\nLoad another save or start a new one.\nCurrent multiworld seed: %x\nFile seed: %x\n~R+~A to force-select.",
            g_patch_ap_settings.mw_seed, p_settings->mw_seed);
            return true;
        }
    }

    return false;
}
