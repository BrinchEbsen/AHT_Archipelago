#ifndef AP_TRIGINFO_H
#define AP_TRIGINFO_H
#include <types.h>
#include <gamestate.h>
#include <minimap_status.h>

#define NUM_SHOP_TRIGINFOS 37
// Trigger info objects used in the game state to keep track of
// shop pads. These can be copied over into the "TrigInfo" array
// in the gamestate to add it to the minimap.
extern GameStateTrigInfo shops_triginfos[];

// Helper array for associating each TrigInfo item in `shops_triginfos`
// with a MapInfo item in `shops_mapinfos`.
extern u8 shop_triginfo_mapinfo_indexes[];

#define NUM_SHOP_MAPINFOS 14
// Mapinfo items for each of the minimaps with shop pads in them.
extern MapOrderInfo shops_mapinfos[];

#endif /* AP_TRIGINFO_H */