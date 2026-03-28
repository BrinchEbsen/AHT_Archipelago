#include <ap_minimap.h>
#include <ap_collectables.h>
#include <ap_settings.h>
#include <wnd.h>
#include <filemanager.h>
#include <hashcodes.h>
#include <minimap_status.h>
#include <system.h>

bool g_show_minimap_icons = false;

void GUI_MiniMap__DrawRestarts__PreCallHOOK(GUI_Base* self, void* pWnd)
{
    if (g_show_minimap_icons) {
        minimap_draw_locations(self, pWnd);
    }
    GUI_MiniMap__DrawRestarts(self, pWnd);
}

void minimap_draw_locations(GUI_Base* self, void* pWnd)
{
    SE_Map* map = GetSpyroMap(0);
    if (map == NULL) {
        return;
    }
    if (map->m_State != Running) {
        return;
    }
    if (map->m_TriggerList.m_pTriggers == NULL) {
        return;
    }

    if (gMiniMapStatus.m_Current.m_FileHash != map->m_MapGeoHashCode) {
        return;
    }
    if (gMiniMapStatus.m_Current.m_MapHash != 0) {
        if (gMiniMapStatus.m_Current.m_MapHash != map->m_MapHashCode) {
            return;
        }
    }

    void* pHeader = SE_FileManager__GetGeoHeader(&gSEFileManager, HT_File_Panel);

    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        size_t byte = (i*2) / 8;
        size_t bit = (i*2) % 8;
        u8 dat = g_gamestate_ap_settings.location_bitfield[byte];

        bool collected = (dat & (0b01 << bit)) != 0;
        bool reachable = (dat & (0b10 << bit)) != 0;

        if (coll->union_type == APC_Objective) {
            // Combine with next objective
            if (coll->objective.include_next) {
                i++;
                byte = (i*2) / 8;
                bit = (i*2) % 8;
                dat = g_gamestate_ap_settings.location_bitfield[byte];
    
                // Both this and the next is collected
                collected = collected && ((dat & (0b01 << bit)) != 0);
            }
        }

        void* pTexture;
        if (collected) {
            pTexture = EXGeoHeader__Texture(pHeader, HT_Texture_CheckBox_Ticked);
        } else {
            pTexture = EXGeoHeader__Texture(pHeader, HT_Texture_CheckBox_Empty);
        }

        EXWnd__SelectSprite2DTexture(pWnd, pTexture, false, false);
        minimap_draw_location(self, pWnd, map, coll, reachable);
    }
}

void minimap_draw_location(
    GUI_Base* self, void* pWnd, SE_Map* map, APCollectable* coll, bool reachable)
{
    if (coll->grabbable.map_index != map->m_MapListIndex) {
        return;
    }

    u16 trig_index;
    if (coll->union_type == APC_Grabbable) {
        trig_index = coll->grabbable.trigger_index;
    } else if (coll->union_type == APC_Objective) {
        trig_index = coll->objective.trigger_index;
    } else {
        return;
    }

    SE_Trigger* trigger = map->m_TriggerList.m_pTriggers[trig_index].m_pSE_Trigger;

    GUI_MiniMap__DrawIcon(
        self,
        trigger->m_Position.x,
        trigger->m_Position.z,
        reachable ? COLOR_LIGHT_GREEN : COLOR_LIGHT_RED,
        8,
        pWnd);
}
