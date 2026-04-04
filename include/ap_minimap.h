#ifndef AP_MINIMAP_H
#define AP_MINIMAP_H
#include <types.h>
#include <gui_base.h>
#include <map.h>
#include <ap_collectables.h>

typedef struct IconPosOverride {
    u16 map_index;
    u16 trigger_index;
    float pos_x;
    float pos_z;
} IconPosOverride;

extern void GUI_MiniMap__DrawRestarts(GUI_Base* self, void* pWnd);
extern void GUI_MiniMap__DrawIcon(GUI_Base* self, float X, float Z, RGBA Col, float HalfSize, void* pWnd);
extern void* EXGeoHeader__Texture(void* self, EXHashCode TextureHash);

extern bool g_show_minimap_icons;

extern IconPosOverride icon_pos_overrides[];

void GUI_MiniMap__DrawRestarts__PreCallHOOK(GUI_Base* self, void* pWnd);
void minimap_draw_locations(GUI_Base* self, void* pWnd);
void minimap_draw_location(
    GUI_Base* self, void* pWnd, SE_Map* map, APCollectable* coll, bool reachable, bool collected);

#endif /* AP_MINIMAP_H */