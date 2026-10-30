#ifndef AP_KEYS_H
#define AP_KEYS_H
#include <types.h>
#include <map.h>
#include <ap_settings.h>

/// @brief Table of all 14 levels with chests.
/// Encoded with RealmID in the upper byte, and LevelID in the lower byte.
extern u16 g_ap_key_list[];

/// @brief Full names of every level with chests.
extern char* g_ap_keys_level_strings[];

/// @brief Shortened names of every level with chests.
extern char* g_ap_keys_level_strings_short[];

/// @brief Letter initials of every level with chests.
extern char g_ap_keys_level_strings_initials[][3];

/// @brief Number of chests in each level.
extern u8 g_ap_keys_num_chests[];

/// @brief Get the index into the `g_ap_keys` arrays that the given map corresponds to.
/// @param map The map to get the index from.
/// @return The index into the `g_ap_keys` arrays that corresponds to this map, or -1
/// if it didn't correspond to any.
int ap_keys_get_level_index(SE_Map* map);

/// @brief Check if a keyring is unlocked for the map.
/// @param map The map.
/// @param out_result True if it's unlocked, false if not.
/// @return Whether the map corresponded to any keyring in the list.
bool ap_keyring_unlocked(SE_Map* map, bool* out_result);

#endif /* AP_KEYS_H */