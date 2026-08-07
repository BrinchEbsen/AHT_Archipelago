#include <ap_collectables.h>
#include <ap_settings.h>
#include <hashcodes.h>
#include <system.h>
#include <util.h>

void ap_set_grabbable(u16 map_index, u16 trigger_index)
{
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->objective != 0xFFFF) {
            continue;
        }

        if ((coll->map_index == map_index) &&
            (coll->trig_index == trigger_index)) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_objective(EXHashCode objective)
{
    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->objective == 0xFFFF) {
            continue;
        }

        if (coll->objective == (objective & 0xFFFF)) {
            ap_set_location(i);
            break;
        }
    }
}

void ap_set_location(int index)
{
    if (!set_u8_bitfield_value(g_gamestate_ap_settings.location_bitfield, index*2, true)) {
        PRINTF("[AP] Set location flag index %d\n", index);
    }
}

s32 num_collectables_in_map(u16 map_index, s32* out_num_collected, s32* out_num_reachable)
{
    s32 num = 0;
    *out_num_collected = 0;
    *out_num_reachable = 0;

    for (int i = 0; i < AP_COLLECTABLES_TOTAL; i++) {
        APCollectable* coll = &g_ap_collectables[i];

        if (coll->map_index != map_index)
        {
            continue;
        }

        num++;

        size_t byte = (i*2) / 8;
        size_t bit = (i*2) % 8;
        u8 dat = g_gamestate_ap_settings.location_bitfield[byte];

        if ((dat & (0b01 << bit)) != 0) {
            (*out_num_collected)++;
        }
        if ((dat & (0b10 << bit)) != 0) {
            (*out_num_reachable)++;
        }
    }

    return num;
}

APCollectable g_ap_collectables[] = {
    #pragma region 19 Sunken Ruins
	{
		.type = LightGem,
		.map_index = 19,
		.trig_index = 0,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 19,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 19,
		.trig_index = 3,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 19,
		.trig_index = 4,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 19,
		.trig_index = 10,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 19,
		.trig_index = 26,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 19,
		.trig_index = 64,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 19,
		.trig_index = 86,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 90,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 91,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 19,
		.trig_index = 92,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 19,
		.trig_index = 93,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 94,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 19,
		.trig_index = 131,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 183,
		.objective = 0xFFFF
	},
    #pragma endregion
	#pragma region 20 Cloudy Domain
    {
		.type = DarkGem,
		.map_index = 20,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 20,
		.trig_index = 8,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 9,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 20,
		.trig_index = 82,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 20,
		.trig_index = 109,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 20,
		.trig_index = 132,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 20,
		.trig_index = 133,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 134,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 135,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 20,
		.trig_index = 136,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 137,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 183,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 20,
		.trig_index = 194,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 20,
		.trig_index = 239,
		.objective = 0xFFFF
	},
    #pragma endregion
	#pragma region 21 Cloudy Domain Ball Gadget
    {
		.type = LightGem,
		.map_index = 21,
		.trig_index = 59,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 21,
		.trig_index = 60,
		.objective = 0xFFFF
	},
    #pragma endregion
	#pragma region 22 Dragonfly Falls
    {
		.type = LightGem,
		.map_index = 22,
		.trig_index = 8,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 11,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 12,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 14,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 15,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 21,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 23,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 29,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 37,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 38,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 22,
		.trig_index = 52,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 73,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 74,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 90,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 22,
		.trig_index = 312,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 313,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 22,
		.trig_index = 314,
		.objective = 0xFFFF
	},
    #pragma endregion
	#pragma region 23 Crocovile Swamp
    {
		.type = DarkGem,
		.map_index = 23,
		.trig_index = 0,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 23,
		.trig_index = 1,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 23,
		.trig_index = 5,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 8,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 23,
		.trig_index = 36,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 48,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 49,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 54,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 58,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 23,
		.trig_index = 62,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 23,
		.trig_index = 68,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 23,
		.trig_index = 103,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 161,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 23,
		.trig_index = 162,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 23,
		.trig_index = 202,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 23,
		.trig_index = 203,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 204,
		.objective = 0xFFFF
	},
    #pragma endregion
	#pragma region 24 Dragon Village
    {
		.type = DarkGem,
		.map_index = 24,
		.trig_index = 1,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 24,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 24,
		.trig_index = 8,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 16,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 24,
		.trig_index = 21,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 92,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 24,
		.trig_index = 139,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 141,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 24,
		.trig_index = 290,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 24,
		.trig_index = 302,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 341,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 24,
		.trig_index = 342,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 24,
		.trig_index = 343,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 30 Dark Mine
	{
		.type = DarkGem,
		.map_index = 30,
		.trig_index = 19,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 83,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 84,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 85,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 86,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 30,
		.trig_index = 87,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 30,
		.trig_index = 88,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 30,
		.trig_index = 89,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 30,
		.trig_index = 150,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 30,
		.trig_index = 211,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 30,
		.trig_index = 214,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 31 Frostbite Village
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 4,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 5,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 6,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 7,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 11,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 31,
		.trig_index = 36,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 31,
		.trig_index = 60,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 31,
		.trig_index = 61,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 66,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 74,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 150,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 170,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 246,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 247,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 312,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 31,
		.trig_index = 372,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 31,
		.trig_index = 373,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 33 Ice Citadel
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 4,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 8,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 11,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 15,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 21,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 22,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 31,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 33,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 36,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 44,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 45,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 33,
		.trig_index = 67,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 33,
		.trig_index = 133,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 33,
		.trig_index = 421,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 35 Gloomy Glacier
	{
		.type = DragonEgg,
		.map_index = 35,
		.trig_index = 1,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 15,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 27,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 35,
		.trig_index = 57,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 58,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 35,
		.trig_index = 212,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 232,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 233,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 35,
		.trig_index = 267,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 35,
		.trig_index = 268,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 40 Reds Laboratory
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 1,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 40,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 40,
		.trig_index = 3,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 40,
		.trig_index = 4,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 40,
		.trig_index = 41,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 109,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 40,
		.trig_index = 110,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 111,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 115,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 40,
		.trig_index = 237,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 388,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 44 Stormy Beach
	{
		.type = DarkGem,
		.map_index = 44,
		.trig_index = 27,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 44,
		.trig_index = 44,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 44,
		.trig_index = 66,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 45 Coastal Remains
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 0,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 3,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 4,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 7,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 11,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 12,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 13,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 19,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 29,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 47,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 45,
		.trig_index = 59,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 119,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 120,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 192,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 60 Molten Mount
	{
		.type = LightGem,
		.map_index = 60,
		.trig_index = 4,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 60,
		.trig_index = 5,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 60,
		.trig_index = 6,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 60,
		.trig_index = 9,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 60,
		.trig_index = 17,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 60,
		.trig_index = 21,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 60,
		.trig_index = 36,
		.objective = 0xFFFF
	},
	{
		.type = DarkGem,
		.map_index = 60,
		.trig_index = 63,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 60,
		.trig_index = 213,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 60,
		.trig_index = 214,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 60,
		.trig_index = 215,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 61 Magma Falls Top
	{
		.type = DragonEgg_Chest,
		.map_index = 61,
		.trig_index = 39,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 61,
		.trig_index = 57,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 62 Magma Falls Ball Gadget
	{
		.type = DragonEgg,
		.map_index = 62,
		.trig_index = 59,
		.objective = 0xFFFF
	},
	{
		.type = DragonEgg,
		.map_index = 62,
		.trig_index = 82,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 62,
		.trig_index = 83,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 62,
		.trig_index = 90,
		.objective = 0xFFFF
	},
    #pragma endregion
    #pragma region 63 Magma Falls Bottom
	{
		.type = DarkGem,
		.map_index = 63,
		.trig_index = 2,
		.objective = 0xFFFF
	},
	{
		.type = EggThief,
		.map_index = 63,
		.trig_index = 10,
		.objective = 0xFFFF
	},
	{
		.type = LightGem,
		.map_index = 63,
		.trig_index = 16,
		.objective = 0xFFFF
	},
	{
		.type = LightGem_Chest,
		.map_index = 63,
		.trig_index = 51,
		.objective = 0xFFFF
	},
    #pragma endregion

    #pragma region Objectives
    // Dragon Village - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 24,
		.trig_index = 158,
		.objective = HT_Objective_MR1_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 24,
		.trig_index = 158,
		.objective = HT_Objective_MR1_AllDone & 0xFFFF,
	},
    // Crocovile Swamp - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 23,
		.trig_index = 6,
		.objective = HT_Objective_MR1_Spy_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 23,
		.trig_index = 6,
		.objective = HT_Objective_MiniGame1A_Complete & 0xFFFF,
	},
    // Crocovile Swamp - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 23,
		.trig_index = 69,
		.objective = HT_Objective_MR1_Blk_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 23,
		.trig_index = 69,
		.objective = HT_Objective_MR1_Blk_AllDone & 0xFFFF,
	},
    // Dragonfly Falls - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 22,
		.trig_index = 283,
		.objective = HT_Objective_MR1_Spx_Egg & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 22,
		.trig_index = 283,
		.objective = HT_Objective_MR1_Spx_AllDone & 0xFFFF,
	},
    // Coastal Remains - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 45,
		.trig_index = 115,
		.objective = HT_Objective_MR2_Blk_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 45,
		.trig_index = 115,
		.objective = HT_Objective_MR2_Blk_AllDone & 0xFFFF,
	},
    // Coastal Remains - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 45,
		.trig_index = 77,
		.objective = HT_Objective_MR2_Spy_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 45,
		.trig_index = 77,
		.objective = HT_Objective_MR2_Spy_AllDone & 0xFFFF,
	},
    // Coastal Remains - Otto
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 150,
		.objective = HT_Objective_OtterNPC_AllDone & 0xFFFF,
	},
    // Sunken Ruins - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 19,
		.trig_index = 65,
		.objective = HT_Objective_MR2_Spx_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 19,
		.trig_index = 65,
		.objective = HT_Objective_MR2_Spx_AllDone & 0xFFFF,
	},
    // Cloudy Domain - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 20,
		.trig_index = 81,
		.objective = HT_Objective_MR2_Sgt_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 20,
		.trig_index = 81,
		.objective = HT_Objective_MR2_Sgt_AllDone & 0xFFFF,
	},
    // Frostbite Village - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 31,
		.trig_index = 244,
		.objective = HT_Objective_MR3_Blk_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 31,
		.trig_index = 244,
		.objective = HT_Objective_MR3_Blk_AllDone & 0xFFFF,
	},
    // Frostbite Village - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 31,
		.trig_index = 242,
		.objective = HT_Objective_MR3_Spy_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 31,
		.trig_index = 242,
		.objective = HT_Objective_MR3_Spy_AllDone & 0xFFFF,
	},
    // Gloomy Glacier - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 35,
		.trig_index = 128,
		.objective = HT_Objective_MR3_Spx_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 35,
		.trig_index = 128,
		.objective = HT_Objective_MR3_Spx_AllDone & 0xFFFF,
	},
    // Gloomy Glacier - Bentley
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 88,
		.objective = HT_Objective_3B_BentleyHasRewarded & 0xFFFF,
	},
    // Ice Citadel - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 33,
		.trig_index = 48,
		.objective = HT_Objective_MR3_Sgt_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 33,
		.trig_index = 48,
		.objective = HT_Objective_MR3_Sgt_AllDone & 0xFFFF,
	},
    // Ice Citadel - Boiler 1
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 97,
		.objective = HT_Objective_3C_LitBoiler_1 & 0xFFFF,
	},
    // Ice Citadel - Boiler 3
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 99,
		.objective = HT_Objective_3C_LitBoiler_3 & 0xFFFF,
	},
    // Ice Citadel - Boiler 5
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 101,
		.objective = HT_Objective_3C_LitBoiler_5 & 0xFFFF,
	},
    // Ice Citadel - Ice Princess
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 47,
		.objective = HT_Objective_3C_IcePrincessHasRewarded & 0xFFFF,
	},
    // Stormy Beach - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 44,
		.trig_index = 8,
		.objective = HT_Objective_MR4_Spy_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 44,
		.trig_index = 8,
		.objective = HT_Objective_MR4_Spy_AllDone & 0xFFFF,
	},
    // Molten Mount - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 60,
		.trig_index = 94,
		.objective = HT_Objective_MR4_Sgt_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 60,
		.trig_index = 94,
		.objective = HT_Objective_MR4_Sgt_AllDone & 0xFFFF,
	},
    // Molten Mount - Teena
	{
		.type = DragonEgg,
		.map_index = 60,
		.trig_index = 93,
		.objective = HT_Objective_TeenaHasRewarded & 0xFFFF,
	},
    // Magma Falls Bottom - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 63,
		.trig_index = 12,
		.objective = HT_Objective_MR4_Spx_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 63,
		.trig_index = 12,
		.objective = HT_Objective_MR4_Spx_AllDone & 0xFFFF,
	},
    // Dark Mine - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 30,
		.trig_index = 154,
		.objective = HT_Objective_MR4_Blk_HalfDone & 0xFFFF,
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 30,
		.trig_index = 154,
		.objective = HT_Objective_MR4_Blk_AllDone & 0xFFFF,
	},
    #pragma endregion

    #pragma region Junk Chests
    // Coastal Remains
	{
		.type = Junk_Chest,
		.map_index = 45,
		.trig_index = 315,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 45,
		.trig_index = 462,
		.objective = 0xFFFF
	},
    // Sunken Ruins
	{
		.type = Junk_Chest,
		.map_index = 19,
		.trig_index = 284,
		.objective = 0xFFFF
	},
    // Cloudy Domain
	{
		.type = Junk_Chest,
		.map_index = 20,
		.trig_index = 243,
		.objective = 0xFFFF
	},
    // Frostbite Village
	{
		.type = Junk_Chest,
		.map_index = 31,
		.trig_index = 232,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 31,
		.trig_index = 485,
		.objective = 0xFFFF
	},
    // Gloomy Glacier
	{
		.type = Junk_Chest,
		.map_index = 35,
		.trig_index = 249,
		.objective = 0xFFFF
	},
    // Ice Citadel
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 286,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 300,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 309,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 377,
		.objective = 0xFFFF
	},
    // Stormy Beach
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 97,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 105,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 168,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 198,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 199,
		.objective = 0xFFFF
	},
    // Molten Mount
	{
		.type = Junk_Chest,
		.map_index = 60,
		.trig_index = 325,
		.objective = 0xFFFF
	},
    // Magma Falls Top
	{
		.type = Junk_Chest,
		.map_index = 61,
		.trig_index = 49,
		.objective = 0xFFFF
	},
    // Dark Mine
	{
		.type = Junk_Chest,
		.map_index = 30,
		.trig_index = 377,
		.objective = 0xFFFF
	},
    // Red's Laboratory
	{
		.type = Junk_Chest,
		.map_index = 40,
		.trig_index = 389,
		.objective = 0xFFFF
	},
	{
		.type = Junk_Chest,
		.map_index = 40,
		.trig_index = 390,
		.objective = 0xFFFF
	},
    #pragma endregion

    #pragma region Dragon Elders
    // Elder Tomas
	{
		.type = NonCollectable,
		.map_index = 24,
		.trig_index = 11,
		.objective = 0x1,
	},
    // Elder Magnus
	{
		.type = NonCollectable,
		.map_index = 23,
		.trig_index = 71,
		.objective = 0x3,
	},
    // Elder Titan
	{
		.type = NonCollectable,
		.map_index = 20,
		.trig_index = 10,
		.objective = 0x9d,
	},
    // Elder Astor
	{
		.type = NonCollectable,
		.map_index = 33,
		.trig_index = 9,
		.objective = 0x9c,
	},
    #pragma endregion

    #pragma region Bosses
    // Gnasty Gnorc
	{
		.type = NonCollectable,
		.map_index = 24,
		.trig_index = 346,
		.objective = 0x81,
	},
    // Ineptune
	{
		.type = NonCollectable,
		.map_index = 45,
		.trig_index = 235,
		.objective = 0x82,
	},
    // Red
	{
		.type = NonCollectable,
		.map_index = 31,
		.trig_index = 318,
		.objective = 0x83,
	},
    // Mecha Red
	{
		.type = NonCollectable,
		.map_index = 40,
		.trig_index = 391,
		.objective = 0x84,
	},
    #pragma endregion

    #pragma region Fireworks
    // Dragon Village
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 304,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 305,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 344,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 431,
		.objective = 0xFFFF
	},
    // Crocovile Swamp
	{
		.type = FireWork,
		.map_index = 23,
		.trig_index = 276,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 23,
		.trig_index = 292,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 23,
		.trig_index = 294,
		.objective = 0xFFFF
	},
    // Sunken Ruins
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 207,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 236,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 252,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 287,
		.objective = 0xFFFF
	},
    // Cloudy Domain
	{
		.type = FireWork,
		.map_index = 20,
		.trig_index = 113,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 20,
		.trig_index = 264,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 20,
		.trig_index = 273,
		.objective = 0xFFFF
	},
    // Ice Citadel
	{
		.type = FireWork,
		.map_index = 33,
		.trig_index = 250,
		.objective = 0xFFFF
	},
    // Stormy Beach
	{
		.type = FireWork,
		.map_index = 44,
		.trig_index = 98,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 44,
		.trig_index = 113,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 44,
		.trig_index = 149,
		.objective = 0xFFFF
	},
    // Molten Mount
	{
		.type = FireWork,
		.map_index = 60,
		.trig_index = 132,
		.objective = 0xFFFF
	},
    // Magma Falls Top
	{
		.type = FireWork,
		.map_index = 61,
		.trig_index = 19,
		.objective = 0xFFFF
	},
    // Dark Mine
	{
		.type = FireWork,
		.map_index = 30,
		.trig_index = 315,
		.objective = 0xFFFF
	},
	{
		.type = FireWork,
		.map_index = 30,
		.trig_index = 366,
		.objective = 0xFFFF
	}
    #pragma endregion
};