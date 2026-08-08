#include <ap_minimap.h>
#include <ap_collectables.h>
#include <ap_settings.h>
#include <wnd.h>
#include <filemanager.h>
#include <hashcodes.h>
#include <minimap_status.h>
#include <system.h>
#include <pad.h>

bool g_show_minimap_icons = false;

// Extra collectable items for the ball gadget stations

APCollectable ballgadgetloc_cloudy_domain = {
    .map_index = 20,
    .trig_index = 77,
    .objective = 0xFFFF,
    .type = NonCollectable,
    .x = 452.590f,
    .z = 65.122f
};
APCollectable ballgadgetloc_magma_falls = {
    .map_index = 61,
    .trig_index = 1,
    .objective = 0xFFFF,
    .type = NonCollectable,
    .x = 260.809f,
    .z = 931.982f
};

void GUI_MiniMap__DrawRestarts__PreCallHOOK(GUI_Base* self, void* pWnd)
{
    if (g_show_minimap_icons) {
        minimap_draw_locations(self, pWnd);
    }
    GUI_MiniMap__DrawRestarts(self, pWnd);
}

void minimap_draw_locations(GUI_Base* self, void* pWnd)
{
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

        // Get whether this item is collected and/or reachable

        size_t byte = (i*2) / 8;
        size_t bit = (i*2) % 8;
        u8 dat = g_gamestate_ap_settings.location_bitfield[byte];

        bool collected = (dat & (0b01 << bit)) != 0;
        bool reachable = (dat & (0b10 << bit)) != 0;

        // If this is a minigame dragon egg, the icon should be combined
        // with the following light gem in the array.
        if (coll->type == DragonEgg_MiniGame) {
            // Advance to next item.
            i++;
            byte = (i*2) / 8;
            bit = (i*2) % 8;
            dat = g_gamestate_ap_settings.location_bitfield[byte];
    
            // Mark collected if both this and the light gem after is collected.
            // We leave reachable alone, we assume it's reachable if the dragon egg is.
            collected = collected && ((dat & (0b01 << bit)) != 0);
        }

        minimap_draw_location(self, pWnd, coll, reachable, collected);
    }

    /*
     * Since there are no minimaps for the ball gadget stages, there's instead
     * a checkbox on the ball gadget stations themselves, which sum up all
     * collectables inside the stage and show a checkbox for whether all of them
     * are reachable/collected.
    */

    // Cloudy Domain Ball Gadget
    if (map->m_MapListIndex == 20) {
        s32 collected;
        s32 reachable;
        s32 num = num_collectables_in_map(21, &collected, &reachable);
        minimap_draw_location(self, pWnd, &ballgadgetloc_cloudy_domain,
            reachable >= num,
            collected >= num);
    }

    // Magma Falls Ball Gadget
    if (map->m_MapListIndex == 61) {
        s32 collected;
        s32 reachable;
        s32 num = num_collectables_in_map(62, &collected, &reachable);
        minimap_draw_location(self, pWnd, &ballgadgetloc_magma_falls,
            reachable >= num,
            collected >= num);
    }
}

void minimap_draw_location(
    GUI_Base* self, void* pWnd, APCollectable* coll, bool reachable, bool collected)
{
    // Only draw fireworks if fireworks are randomized
    if ((coll->type == FireWork) && !g_gamestate_ap_settings.fireworks_are_randomized)
    {
        return;
    }

    // Get texture to draw
    void* pHeader = SE_FileManager__GetGeoHeader(&gSEFileManager, HT_File_Panel);
    void* pTexture;
    if (collected) {
        pTexture = EXGeoHeader__Texture(pHeader, HT_Texture_CheckBox_Ticked);
    } else {
        pTexture = EXGeoHeader__Texture(pHeader, HT_Texture_CheckBox_Empty);
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
        reachable ? COLOR_LIGHT_GREEN : COLOR_LIGHT_RED, // Draw in green if reachable
        8,
        pWnd);
}
