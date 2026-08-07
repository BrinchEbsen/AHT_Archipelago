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
    EXHashCode file_hash = gMiniMapStatus.m_Current.m_FileHash;
    EXHashCode map_hash = gMiniMapStatus.m_Current.m_MapHash;

    if ((map_hash & 0xFF000000) != HT_Map_HASHCODE_BASE)
    {
        map_hash = 0;
    }

    SE_Map* map = SE_MapList__FindMap(&gMapList, file_hash, map_hash);

    if (map == NULL)
    {
        return;
    }

    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (map->m_MapListIndex != coll->map_index)
        {
            continue;
        }

        size_t byte = (i*2) / 8;
        size_t bit = (i*2) % 8;
        u8 dat = g_gamestate_ap_settings.location_bitfield[byte];

        bool collected = (dat & (0b01 << bit)) != 0;
        bool reachable = (dat & (0b10 << bit)) != 0;

        if (coll->type == DragonEgg_MiniGame) {
            // Combine with next objective
            i++;
            byte = (i*2) / 8;
            bit = (i*2) % 8;
            dat = g_gamestate_ap_settings.location_bitfield[byte];
    
            // Both this and the next is collected
            collected = collected && ((dat & (0b01 << bit)) != 0);
        }

        minimap_draw_location(self, pWnd, coll, reachable, collected);
    }

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
    if ((coll->type == FireWork) && !g_gamestate_ap_settings.fireworks_are_randomized)
    {
        return;
    }

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
        reachable ? COLOR_LIGHT_GREEN : COLOR_LIGHT_RED,
        8,
        pWnd);
}
