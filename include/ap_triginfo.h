#ifndef AP_TRIGINFO_H
#define AP_TRIGINFO_H
#include <types.h>
#include <gamestate.h>
#include <minimap_status.h>

#define NUM_SHOP_TRIGINFOS 37
extern GameStateTrigInfo shops_triginfos[];
extern u8 shop_triginfo_mapinfo_indexes[];
#define NUM_SHOP_MAPINFOS 14
extern MapOrderInfo shops_mapinfos[];

#endif /* AP_TRIGINFO_H */