#include <cutscene_skip.h>
#include <map.h>
#include <pad.h>
#include <player.h>
#include <ap_settings.h>
#include <hashcodes.h>

// Cutscenes that crash/cause issues and thus should not be skipped
FileSceneHash cutscenes_to_ignore[] = {
    {
        .file_hash = HT_File_C47_R3C,
        .scene_hash = HT_Script_CutsceneF
    }
};
#define NUM_CUTSCENES_TO_IGNORE 1

int XItemHandler_Cutscene__Update_VtableHook(void *self)
{
    if (g_gamestate_ap_settings.skip_cutscene_button && g_pad_button_edge_down(PAD_BUTTON_Y)) {
        bool ignore = false;
        for (int i = 0; i < NUM_CUTSCENES_TO_IGNORE; i++) {
            if ((XITEMHANDLER_CUTSCENE_M_FILE_HASH(self) == cutscenes_to_ignore[i].file_hash) &&
                (XITEMHANDLER_CUTSCENE_M_SCENE_HASH(self) == cutscenes_to_ignore[i].scene_hash)) {
                ignore = true;
                break;
            }
        }

        if (!ignore) {
            // We don't want to skip the "cutscene" in the
            // title or loading screen, as this causes a crash.
            m_States loading_state = GET_MAP_LOADING->m_State;
            m_States titles_state = GET_MAP_TITLES->m_State;
            
            if ((loading_state != Running) && (titles_state != Running)) {
                skip_cutscene(self);
            }
        }
    }

    return XItemHandler_Cutscene__Update(self);
}

void skip_cutscene(void* p_cutscene)
{
    bool controls_locked = true;
    if (gpPlayer != NULL) {
        controls_locked = XSEItemHandler_Player__ControlsLocked(gpPlayer);
    }

    if (controls_locked) {
        void* script = XITEMHANDLER_CUTSCENE_M_PSCRIPT(p_cutscene);
        EXItemAnimator_Script__SetScriptStatus(script, 3);
    }
}
