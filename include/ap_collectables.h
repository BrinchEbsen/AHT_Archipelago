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

/// @brief An item in the game, in the form of either a "grabbable" 
/// item in the world, or an "objective" from performing a task.
typedef struct APCollectable
{
    /// @brief Which type of collectable this is.
    /// Uses enum type `APCollectable_Type`.
    u8 type;
    /// @brief Index of the map which contains this item.
    u8 map_index;
    /// @brief Index of the trigger associated with this item.
    u16 trig_index;
    /// @brief Objective for objective-based items. Set to `0xFFFF` if
    /// it's not an objective.
    u16 objective;
    /// @brief The x-position of the item in the world.
    float x;
    /// @brief The z-position of the item in the world.
    float z;
} APCollectable;

// Total number of entries in `g_ap_collectables`.
#define AP_COLLECTABLES_TOTAL 271

/// @brief Mark a grabbable item collected.
/// @param map_index Map index of the grabbable item's trigger.
/// @param trigger_index Index of the grabbable item's trigger.
void ap_set_grabbable(u16 map_index, u16 trigger_index);

/// @brief Mark an objective item collected.
/// @param objective Objective hashcode of the item.
void ap_set_objective(EXHashCode objective);

/// @brief Mark a location as collected.
/// @param index Index of the location into `g_ap_collectables`.
void ap_set_location(int index);

/// @brief Tally up all items in a map, and how many are reachable/collected.
/// @param map_index Index of the map.
/// @param out_num_collected Amount of items collected.
/// @param out_num_reachable Amount of items reachable.
/// @return Total number of items.
s32 num_collectables_in_map(u16 map_index, s32* out_num_collected, s32* out_num_reachable);

// The collectables array.
extern APCollectable g_ap_collectables[];

#endif /* AP_COLLECTABLES */
