#ifndef AP_MINIMAP_H
#define AP_MINIMAP_H
#include <types.h>
#include <gui_base.h>
#include <map.h>
#include <ap_collectables.h>

extern void GUI_MiniMap__DrawRestarts(GUI_Base* self, void* pWnd);
extern void GUI_MiniMap__DrawIcon(GUI_Base* self, float X, float Z, RGBA Col, float HalfSize, void* pWnd);
extern void* EXGeoHeader__Texture(void* self, EXHashCode TextureHash);

extern bool g_show_minimap_icons;

// Hook into the minimap's routine of drawing shop pads to draw the locations.
void GUI_MiniMap__DrawRestarts__PreCallHOOK(GUI_Base* self, void* pWnd);

// Draw all locations on the minimap as checkboxes.
void minimap_draw_locations(GUI_Base* self, void* pWnd);

/// @brief Draw a location checkbox onto the minimap.
/// @param self this-pointer (GUI_MiniMap)
/// @param pWnd Window
/// @param coll Collectable to draw
/// @param reachable Whether the collectable is reachable (determines checkbox color)
/// @param collected Whether the collectable is collected (determines whether box is checked)
void minimap_draw_location(
    GUI_Base* self, void* pWnd, APCollectable* coll, bool reachable, bool collected);

#endif /* AP_MINIMAP_H */