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
    LightGem_MiniGame,
    DragonEgg_MiniGame,
    EggThief,
    Junk_Chest,
    NonCollectable,
    FireWork
} APCollectable_Type;

typedef struct APCollectable
{
    u8 type;
    u8 map_index;
    u16 trig_index;
    u16 objective;
    float x;
    float z;
} APCollectable;

#define AP_COLLECTABLES_TOTAL 271

void ap_set_grabbable(u16 map_index, u16 trigger_index);

void ap_set_objective(EXHashCode objective);

void ap_set_location(int index);

s32 num_collectables_in_map(u16 map_index, s32* out_num_collected, s32* out_num_reachable);

extern APCollectable g_ap_collectables[];

#endif /* AP_COLLECTABLES */
