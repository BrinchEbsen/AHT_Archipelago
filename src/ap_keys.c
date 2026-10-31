#include <util.h>
#include <ap_keys.h>
#include <ap_settings.h>

// Entries are stored as 0xRRLL (Realm and Level id's)

u16 g_ap_key_list[] = {
    // Dragon Village
    ( Realm_1 << 8 ) | Level_A, // 0
    // Crocovile Swamp
    ( Realm_1 << 8 ) | Level_B, // 1
    // Dragonfly Falls
    ( Realm_1 << 8 ) | Level_C, // 2
    
    // Coastal Remains
    ( Realm_2 << 8 ) | Level_A, // 3
    // Sunken Ruins
    ( Realm_2 << 8 ) | Level_B, // 4
    // Cloudy Domain
    ( Realm_2 << 8 ) | Level_C, // 5

    // Frostbite Village
    ( Realm_3 << 8 ) | Level_A, // 6
    // Gloomy Glacier
    ( Realm_3 << 8 ) | Level_B, // 7
    // Ice Citadel
    ( Realm_3 << 8 ) | Level_C, // 8

    // Stormy Beach
    ( Realm_4 << 8 ) | Level_A, // 9
    // Molten Mount
    ( Realm_4 << 8 ) | Level_B, // 10
    // Magma Falls
    ( Realm_4 << 8 ) | Level_C, // 11
    // Dark Mine
    ( Realm_4 << 8 ) | Level_D, // 12
    // Red's Laboratory
    ( Realm_4 << 8 ) | Level_E  // 13
};

char* g_ap_keys_level_strings[] = {
    "Dragon Village",
    "Crocovile Swamp",
    "Dragonfly Falls",
    "Coastal Remains",
    "Sunken Ruins",
    "Cloudy Domain",
    "Frostbite Village",
    "Gloomy Glacier",
    "Ice Citadel",
    "Stormy Beach",
    "Molten Mount",
    "Magma Falls",
    "Dark Mine",
    "Red's Laboratory"
};

char* g_ap_keys_level_strings_short[] = {
    "Dragon V.",
    "Crocovile S.",
    "Dragonfly F.",
    "Coastal R.",
    "Sunken R.",
    "Cloudy D.",
    "Frostbite V.",
    "Gloomy G.",
    "Ice C.",
    "Stormy B.",
    "Molten M.",
    "Magma F.",
    "Dark M.",
    "Red's L."
};

char g_ap_keys_level_strings_initials[][3] = {
    "DV",
    "CS",
    "DF",
    "CR",
    "SR",
    "CD",
    "FV",
    "GG",
    "IC",
    "SB",
    "MM",
    "MF",
    "DM",
    "RL"
};

u8 g_ap_keys_num_chests[] = {
    // Dragon Village
    3,
    // Crocovile Swamp
    3,
    // Dragonfly Falls
    2,
    
    // Coastal Remains
    2,
    // Sunken Ruins
    8,
    // Cloudy Domain
    4,

    // Frostbite Village
    4,
    // Gloomy Glacier
    3,
    // Ice Citadel
    6,

    // Stormy Beach
    5,
    // Molten Mount
    4,
    // Magma Falls
    3,
    // Dark Mine
    3,
    // Red's Laboratory
    2
};

int ap_keys_get_level_index(SE_Map* map)
{
    if (map == NULL) {
        return -1;
    }

    if ((map->m_RealmID == 0) || (map->m_LevelID == 0)) {
        return -1;
    }

    // Combine realm and level ID to match against format in the array
    u16 realm_level = ( map->m_RealmID << 8 ) | map->m_LevelID;

    for (int i = 0; i < AP_KEYS_NUM_LEVELS; i++)
    {
        if (realm_level == g_ap_key_list[i])
        {
            return i;
        }
    }

    return -1;
}

bool ap_keyring_unlocked(SE_Map* map, bool* out_result)
{
    *out_result = false;

    int index = ap_keys_get_level_index(map);

    if (index < 0)
    {
        return false;
    }

    *out_result = get_u8_bitfield_value(g_gamestate_ap_settings.keyring_bitfield, index);

    return true;
}
