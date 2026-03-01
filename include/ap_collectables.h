#ifndef AP_COLLECTABLES
#define AP_COLLECTABLES
#include <types.h>

typedef enum APCollectable_Type
{
    LightGem,
    DragonEgg,
    DarkGem,
    LightGem_Chest,
    DragonEgg_Chest,
    EggThief
} APCollectable_Type;

typedef enum APCollectable_UnionType
{
    APC_Grabbable,
    APC_Objective
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

typedef struct APCollectable
{
    APCollectable_UnionType union_type;
    union {
        APCollectable_Grabbable grabbable;
        APCollectable_Objective objective;
    };
} APCollectable;

#define AP_GRABBABLE_START 0
#define AP_GRABBABLE_NUM 181
#define AP_OBJECTIVES_START AP_GRABBABLE_NUM
#define AP_OBJECTIVES_NUM 39

void ap_set_collectable(int index);

extern APCollectable g_ap_collectables[];

#endif /* AP_COLLECTABLES */