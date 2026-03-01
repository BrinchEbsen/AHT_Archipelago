#ifndef AP_COLLECTABLES
#define AP_COLLECTABLES
#include <types.h>

typedef enum APCollectable_Type
{
    LightGem,
    DragonEgg,
    DarkGem,
    LightGem_Chest,
    DragonEgg_Chest
} APCollectable_Type;

typedef enum APCollectable_UnionType
{
    APC_Grabbable,
    APC_Objective,
    APC_Boiler
} APCollectable_UnionType;

typedef struct APCollectable_Grabbable
{
    u16 trigger_index;
    u16 map_index;
    APCollectable_Type type;
} APCollectable_Grabbable;

typedef struct APCollectable_Objective
{
    EXHashCode objective;
    APCollectable_Type type;
} APCollectable_Objective;

typedef struct APCollectable_Boiler
{
    // Always in Ice Citadel and always a light gem
    u16 trigger_index;
} APCollectable_Boiler;

typedef struct APCollectable
{
    APCollectable_UnionType union_type;
    union {
        APCollectable_Grabbable grabbable;
        APCollectable_Objective npc;
        APCollectable_Boiler boiler;
    };
} APCollectable;

#define NUM_AP_GRABBABLE 169

extern APCollectable g_ap_collectables[];

#endif /* AP_COLLECTABLES */