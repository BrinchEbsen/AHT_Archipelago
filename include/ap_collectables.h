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
    EggThief,
    Junk_Chest,
    NonCollectable
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
    u16 trigger_index;
    u16 map_index;
    EXHashCode objective;
    // This objective stems from the same trigger/NPC as the next one
    bool include_next;
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

#define AP_COLLECTABLES_TOTAL 249

void ap_set_grabbable(u16 map_index, u16 trigger_index);

void ap_set_objective(EXHashCode objective);

void ap_set_location(int index);

extern APCollectable g_ap_collectables[];

#endif /* AP_COLLECTABLES */