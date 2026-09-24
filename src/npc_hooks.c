#include <npc_hooks.h>
#include <trigger.h>
#include <hashcodes.h>
#include <ap_settings.h>
#include <map.h>

int XSEItemHandler_NPC__InitNPC_PreCallHook(void* self)
{
    SE_Trigger* ptrigger = OFFSET_VAL(SE_Trigger*, self, 0x10);
    EXHashCode geo_ref = ptrigger->m_EXTrigger.m_GeoFileHashRef;

    // Returning -1 "kills" (deletes) the object.

    if (g_gamestate_ap_settings.minigame_blink_config == MinigameConfig_Disabled)
    {
        if (geo_ref == HT_File_BlinkyNPC)
        {
            return -1;
        }
    }

    if (g_gamestate_ap_settings.minigame_sgtbyrd_config == MinigameConfig_Disabled)
    {
        if (geo_ref == HT_File_SgtBirdNPC)
        {
            return -1;
        }
    }

    if (g_gamestate_ap_settings.minigame_turret_config == MinigameConfig_Disabled)
    {
        EXHashCode data_0 = ptrigger->m_EXTrigger.m_Data[0].h;
        switch (data_0)
        {
            case HT_File_FredTheFrog:
            case HT_File_TurtleMum:
            case HT_File_PeggyNPC:
            case HT_File_WallyWalrus:
                return -1;
        }
    }

    if (g_gamestate_ap_settings.minigame_sparx_config == MinigameConfig_Disabled)
    {
        EXHashCode gfx_ref = ptrigger->m_EXTrigger.m_GfxHashRef;
        switch (((SE_Map*)ptrigger->m_pMap)->m_MapListIndex)
        {
            // Sunken Ruins
            case 19: if (gfx_ref == 0x8200002c) return -1; break;
            // Dragonfly Falls
            case 22: if (gfx_ref == 0x82000061) return -1; break;
            // Gloomy Glacier
            case 35: if (gfx_ref == 0x82000023) return -1; break;
            // Magma Falls Bottom
            case 63: if (gfx_ref == 0x82000018) return -1; break;
        }
    }

    return XSEItemHandler_NPC__InitNPC(self);
}
