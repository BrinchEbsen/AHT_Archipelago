#ifndef AP_KEYRING_H
#define AP_KEYRING_H
#include <types.h>
#include <map.h>

#define AP_NUM_KEYRINGS 14

extern u16 g_ap_keyring_list[];

extern wchar16* g_ap_keyring_shop_strings[];

extern char* g_ap_keyring_pausemenu_strings[];

extern u8 g_ap_keyring_num_chests[];

/// @brief Check if a keyring is unlocked for the map.
/// @param map The map.
/// @param out_result True if it's unlocked, false if not.
/// @return Whether the map corresponded to any keyring in the list.
bool ap_keyring_unlocked(SE_Map* map, bool* out_result);

#endif /* AP_KEYRING_H */