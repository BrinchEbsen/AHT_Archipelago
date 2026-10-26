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

typedef enum MinigameType
{
    MinigameType_None,
    MinigameType_Blink,
    MinigameType_Sparx,
    MinigameType_Turret,
    MinigameType_SgtByrd
} MinigameType;

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
    /// @brief The type of minigame objective (if it is one).
    /// Uses enum type `MinigameType`.
    u8 minigame_type;
    /// @brief The x-position of the item in the world.
    float x;
    /// @brief The z-position of the item in the world.
    float z;
} APCollectable;

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

/// @brief Get the state of a collectable.
/// @param index Index of the collectable.
/// @param out_collected Whether the collectable is collected.
/// @param out_reachable Whether the collectable is reachable.
/// @param out_reachable_trick Whether the collectable is reachable with tricks.
void get_collectable_state(size_t index, bool* out_collected, bool* out_reachable, bool* out_reachable_trick);

/// @brief Tally up all items in a map and their states.
/// @param map_index Index of the map.
/// @param out_num_collected Amount of items collected.
/// @param out_num_reachable Amount of items reachable.
/// @param out_num_reachable_trick Amount of items reachable with tricks.
/// @return Total number of items.
s32 num_collectables_in_map(u16 map_index, s32* out_num_collected, s32* out_num_reachable, s32* out_num_reachable_trick);

/// @brief Get whether a collectable's source minigame is set to "easy only" or "disabled" in the settings.
/// @param coll The collectable.
/// @param out_easyonly Whether this minigame is set to "easy only".
/// @param out_disabled Whether this minigame is set to "disabled".
/// @return Whether this is a minigame collectable at all.
bool get_minigame_collectable_config(APCollectable* coll, bool* out_easyonly, bool* out_disabled);

// The collectables array.
extern APCollectable g_ap_collectables[];

#endif /* AP_COLLECTABLES */
