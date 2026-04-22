#include <util.h>
#include <ap_keyring.h>
#include <ap_settings.h>

// Entries are stored as 0xRRLL (Realm and Level id's)

u16 g_ap_keyring_list[] = {
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

wchar16* g_ap_keyring_shop_strings[] = {
    u"Dragon Village key ring",
    u"Crocovile Swamp key ring",
    u"Dragonfly Falls key ring",
    u"Coastal Remains key ring",
    u"Sunken Ruins key ring",
    u"Cloudy Domain key ring",
    u"Frostbite Village key ring",
    u"Gloomy Glacier key ring",
    u"Ice Citadel key ring",
    u"Stormy Beach key ring",
    u"Molten Mount key ring",
    u"Magma Falls key ring",
    u"Dark Mine key ring",
    u"Red's Laboratory key ring"
};

char* g_ap_keyring_pausemenu_strings[] = {
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

u8 g_ap_keyring_num_chests[] = {
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
    3,

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

bool ap_keyring_unlocked(SE_Map* map, bool* out_result)
{
    *out_result = false;

    if (map == NULL) {
        return false;
    }

    if ((map->m_RealmID == 0) || (map->m_LevelID == 0)) {
        return false;
    }

    u16 realm_level = ( map->m_RealmID << 8 ) | map->m_LevelID;

    for (int i = 0; i < AP_NUM_KEYRINGS; i++) {
        if (realm_level == g_ap_keyring_list[i]) {
            *out_result = get_u8_bitfield_value(g_gamestate_ap_settings.keyring_bitfield, i);
            return true;
        }
    }

    return false;
}
