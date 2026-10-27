#include <ap_minimap.h>
#include <ap_collectables.h>
#include <ap_settings.h>
#include <wnd.h>
#include <filemanager.h>
#include <hashcodes.h>
#include <minimap_status.h>
#include <system.h>
#include <pad.h>
#include <mapindex.h>
#include <util.h>
#include <ap_handler.h>

// Extra collectable items for the ball gadget stations

APCollectable ballgadgetloc_cloudy_domain = {
    .map_index = MI_CloudyDomain,
    .trig_index = 77,
    .objective = 0xFFFF,
    .type = NonCollectable,
    .x = 452.590f,
    .z = 65.122f
};
APCollectable ballgadgetloc_magma_falls = {
    .map_index = MI_MagmaFallsTop,
    .trig_index = 1,
    .objective = 0xFFFF,
    .type = NonCollectable,
    .x = 260.809f,
    .z = 931.982f
};

u8 trick_flasher_cycle = 0;

void GUI_MiniMap__DrawRestarts__PreCallHOOK(GUI_Base* self, void* pWnd)
{
    if (g_gamestate_ap_settings.ut_enabled) {
        minimap_draw_locations(self, pWnd);
    }
    GUI_MiniMap__DrawRestarts(self, pWnd);
}

void minimap_update_trick_flashing(GUI_Base* self)
{
    s32 cycle = (self->m_UpdateCounter % 0x40) * 4;
    
    if (cycle > 0x80) {
        cycle = 0x80 - (cycle - 0x80);
    }

    if (cycle < 0x40) {
        cycle = 0x40;
    }

    trick_flasher_cycle = cycle;
}

void minimap_draw_locations(GUI_Base* self, void* pWnd)
{
    has_opened_minimap = true;

    minimap_update_trick_flashing(self);

    // This is the "currently viewed" minimap.
    EXHashCode file_hash = gMiniMapStatus.m_Current.m_FileHash;
    EXHashCode map_hash = gMiniMapStatus.m_Current.m_MapHash;

    // The "FindMap" function only checks map hash if it's non-zero.
    // We force it zero if map hash is irrelevant, just for safety.
    if ((map_hash & 0xFF000000) != HT_Map_HASHCODE_BASE)
    {
        map_hash = 0;
    }

    // Get the actual map we're looking at.
    SE_Map* map = SE_MapList__FindMap(&gMapList, file_hash, map_hash);
    if (map == NULL)
    {
        return;
    }

    // Cycle through all items and draw the relevant ones.
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        // Skip any that aren't in this map.
        if (map->m_MapListIndex != coll->map_index)
        {
            continue;
        }

        bool easyonly = false;
        bool disable = false;

        get_minigame_collectable_config(coll, &easyonly, &disable);

        if (disable)
        {
            continue;
        }

        // Get whether this item is collected and/or reachable

        bool collected;
        bool reachable;
        bool reachable_trick;

        get_collectable_state(i, &collected, &reachable, &reachable_trick);

        // If this is a minigame dragon egg, the icon should be combined
        // with the following light gem in the array.
        if (coll->type == DragonEgg_MiniGame) {
            // Advance to next item.
            i++;

            // Whether we logically count the light gem
            if (!easyonly)
            {
                bool next_collectable = get_u8_bitfield_value(g_gamestate_ap_settings.location_bitfield_collected, i);

                // Mark collected if both this and the light gem after is collected.
                // We leave reachable alone, we assume it's reachable if the dragon egg is.
                collected = collected && next_collectable;
            }
        }

        minimap_draw_location(self, pWnd, coll, collected, reachable, reachable_trick);
    }

    /*
     * Since there are no minimaps for the ball gadget stages, there's instead
     * a checkbox on the ball gadget stations themselves, which sum up all
     * collectables inside the stage and show a checkbox for whether all of them
     * are reachable/collected.
    */

    // Cloudy Domain Ball Gadget
    if (map->m_MapListIndex == MI_CloudyDomain) {
        s32 collected;
        s32 reachable;
        s32 reachable_trick;
        s32 num = num_collectables_in_map(MI_CloudyDomainBallGadget, &collected, &reachable, &reachable_trick);
        minimap_draw_location(self, pWnd, &ballgadgetloc_cloudy_domain,
            collected >= num,
            reachable >= num,
            reachable_trick >= num);
    }

    // Magma Falls Ball Gadget
    if (map->m_MapListIndex == MI_MagmaFallsTop) {
        s32 collected;
        s32 reachable;
        s32 reachable_trick;
        s32 num = num_collectables_in_map(MI_MagmaFallsBallGadget, &collected, &reachable, &reachable_trick);
        minimap_draw_location(self, pWnd, &ballgadgetloc_magma_falls,
            reachable >= num,
            collected >= num,
            reachable_trick >= num);
    }
}

void minimap_draw_location(
    GUI_Base* self, void* pWnd, APCollectable* coll, bool collected, bool reachable, bool reachable_trick)
{
    // Only draw fireworks if fireworks are randomized
    if ((coll->type == FireWork) && !g_gamestate_ap_settings.fireworks_are_randomized)
    {
        return;
    }

    // Get texture to draw
    void* pHeader = SE_FileManager__GetGeoHeader(&gSEFileManager, HT_File_Panel);
    void* pTexture;
    RGBA col;

    if (collected)
    {
        pTexture = EXGeoHeader__Texture(pHeader, HT_Texture_CheckBox_Ticked);
        col = COLOR_LIGHT_GREEN;
    }
    else
    {
        pTexture = EXGeoHeader__Texture(pHeader, HT_Texture_CheckBox_Empty);

        if (reachable)
        {
            col = COLOR_WHITE; // Yellow (base texture)
        }
        else
        {
            if (reachable_trick)
            {
                col = COLOR_RGBA(0x80, trick_flasher_cycle, trick_flasher_cycle, 0x80);
            }
            else
            {
                col = COLOR_LIGHT_RED;
            }
        }
    }

    EXWnd__SelectSprite2DTexture(pWnd, pTexture, false, false);

    if ((coll->x == 0.0f) || (coll->z == 0.0f))
    {
        PRINTF("ATTEMPTED TO DRAW AT 0,0 (m: %d, t: %d)\n", coll->map_index, coll->trig_index);
    }

    GUI_MiniMap__DrawIcon(
        self,
        coll->x,
        coll->z,
        col,
        8,
        pWnd);
}
