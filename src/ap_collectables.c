#include <ap_collectables.h>
#include <ap_settings.h>
#include <hashcodes.h>
#include <system.h>

APCollectable g_ap_collectables[] = {
    #pragma region 19 Sunken Ruins
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 0,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 2,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 3,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 4,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 10,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 26,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 64,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 86,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 90,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 91,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 92,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 93,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 94,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 131,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 183,
            .type = LightGem_Chest
        }
    },
    #pragma endregion
    #pragma region 20 Cloudy Domain
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 2,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 8,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 9,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 82,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 109,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 132,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 133,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 134,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 135,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 136,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 137,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 183,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 194,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 239,
            .type = EggThief
        }
    },
    #pragma endregion
    #pragma region 21 Cloudy Domain Ball Gadget
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 21,
            .trigger_index = 59,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 21,
            .trigger_index = 60,
            .type = DragonEgg
        }
    },
    #pragma endregion
    #pragma region 22 Dragonfly Falls
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 8,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 11,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 12,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 14,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 15,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 21,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 23,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 29,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 37,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 38,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 52,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 73,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 74,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 90,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 312,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 313,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 22,
            .trigger_index = 314,
            .type = LightGem_Chest
        }
    },
    #pragma endregion
    #pragma region 23 Crocovile Swamp
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 0,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 1,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 5,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 8,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 36,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 48,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 49,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 54,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 58,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 62,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 68,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 103,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 161,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 162,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 202,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 203,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 23,
            .trigger_index = 204,
            .type = LightGem
        }
    },
    #pragma endregion
    #pragma region 24 Dragon Village
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 1,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 2,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 8,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 16,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 21,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 92,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 139,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 141,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 290,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 302,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 341,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 342,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 24,
            .trigger_index = 343,
            .type = LightGem_Chest
        }
    },
    #pragma endregion
    #pragma region 30 Dark Mine
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 19,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 83,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 84,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 85,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 86,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 87,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 88,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 89,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 150,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 211,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 214,
            .type = DragonEgg
        }
    },
    #pragma endregion
    #pragma region 31 Frostbite Village
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 4,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 5,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 6,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 7,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 11,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 36,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 60,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 61,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 66,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 74,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 150,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 170,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 246,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 247,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 312,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 372,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 373,
            .type = DragonEgg_Chest
        }
    },
    #pragma endregion
    #pragma region 33 Ice Citadel
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 4,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 8,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 11,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 15,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 21,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 22,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 31,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 33,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 36,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 44,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 45,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 67,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 133,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 421,
            .type = DragonEgg_Chest
        }
    },
    #pragma endregion
    #pragma region 35 Gloomy Glacier
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 1,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 2,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 15,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 27,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 57,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 58,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 212,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 232,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 233,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 267,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 268,
            .type = DragonEgg_Chest
        }
    },
    #pragma endregion
    #pragma region 40 Reds Laboratory
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 1,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 2,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 3,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 4,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 41,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 109,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 110,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 111,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 115,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 237,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 388,
            .type = LightGem
        }
    },
    #pragma endregion
    #pragma region 44 Stormy Beach
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 27,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 44,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 66,
            .type = EggThief
        }
    },
    #pragma endregion
    #pragma region 45 Coastal Remains
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 0,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 2,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 3,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 4,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 7,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 11,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 12,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 13,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 19,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 29,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 47,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 59,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 119,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 120,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 192,
            .type = LightGem
        }
    },
    #pragma endregion
    #pragma region 60 Molten Mount
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 4,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 5,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 6,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 9,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 17,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 21,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 36,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 63,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 213,
            .type = LightGem_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 214,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 215,
            .type = LightGem_Chest
        }
    },
    #pragma endregion
    #pragma region 61 Magma Falls Top
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 61,
            .trigger_index = 39,
            .type = DragonEgg_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 61,
            .trigger_index = 57,
            .type = LightGem
        }
    },
    #pragma endregion
    #pragma region 62 Magma Falls Ball Gadget
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 62,
            .trigger_index = 59,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 62,
            .trigger_index = 82,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 62,
            .trigger_index = 83,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 62,
            .trigger_index = 90,
            .type = LightGem
        }
    },
    #pragma endregion
    #pragma region 63 Magma Falls Bottom
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 63,
            .trigger_index = 2,
            .type = DarkGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 63,
            .trigger_index = 10,
            .type = EggThief
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 63,
            .trigger_index = 16,
            .type = LightGem
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 63,
            .trigger_index = 51,
            .type = LightGem_Chest
        }
    },
    #pragma endregion

    #pragma region Objectives
    // Dragon Village - Sgt. Byrd
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_AllDone,
            .type = LightGem
        }
    },

    // Crocovile Swamp - Turret
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_Spy_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MiniGame1A_Complete,
            .type = LightGem
        }
    },

    // Crocovile Swamp - Blink
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_Blk_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_Blk_AllDone,
            .type = LightGem
        }
    },
    
    // Dragonfly Falls - Sparx
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_Spx_Egg,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR1_Spx_AllDone,
            .type = LightGem
        }
    },
    
    // Coastal Remains - Blink
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Blk_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Blk_AllDone,
            .type = LightGem
        }
    },
    
    // Coastal Remains - Turret
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Spy_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Spy_AllDone,
            .type = LightGem
        }
    },

    // Coastal Remains - Otto
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_OtterNPC_AllDone,
            .type = LightGem
        }
    },
    
    // Sunken Ruins - Sparx
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Spx_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Spx_AllDone,
            .type = LightGem
        }
    },
    
    // Cloudy Domain - Sgt. Byrd
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Sgt_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR2_Sgt_AllDone,
            .type = LightGem
        }
    },
    
    // Frostbite Village - Blink
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Blk_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Blk_AllDone,
            .type = LightGem
        }
    },
    
    // Frostbite Village - Turret
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Spy_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Spy_AllDone,
            .type = LightGem
        }
    },
    
    // Gloomy Glacier - Sparx
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Spx_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Spx_AllDone,
            .type = LightGem
        }
    },

    // Gloomy Glacier - Bentley
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_3B_BentleyHasRewarded,
            .type = LightGem
        }
    },
    
    // Ice Citadel - Sgt. Byrd
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Sgt_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR3_Sgt_AllDone,
            .type = LightGem
        }
    },

    // Ice Citadel - Boiler 1
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_3C_LitBoiler_1,
            .type = LightGem
        }
    },

    // Ice Citadel - Boiler 3
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_3C_LitBoiler_3,
            .type = LightGem
        }
    },

    // Ice Citadel - Boiler 5
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_3C_LitBoiler_5,
            .type = LightGem
        }
    },

    // Ice Citadel - Ice Princess
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_3C_IcePrincessHasRewarded,
            .type = LightGem
        }
    },
    
    // Stormy Beach - Turret
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Spy_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Spy_AllDone,
            .type = LightGem
        }
    },
    
    // Molten Mount - Sgt. Byrd
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Sgt_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Sgt_AllDone,
            .type = LightGem
        }
    },

    // Molten Mount - Teena
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_TeenaHasRewarded,
            .type = DragonEgg
        }
    },
    
    // Magma Falls Bottom - Sparx
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Spx_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Spx_AllDone,
            .type = LightGem
        }
    },
    
    // Dark Mine - Blink
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Blk_HalfDone,
            .type = DragonEgg
        }
    },
    {
        .union_type = APC_Objective,
        .objective = {
            .objective = HT_Objective_MR4_Blk_AllDone,
            .type = LightGem
        }
    },
    #pragma endregion

    #pragma region Junk Chests
    // Coastal Remains
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 315,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 45,
            .trigger_index = 462,
            .type = Junk_Chest
        }
    },
    // Sunken Ruins
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 19,
            .trigger_index = 284,
            .type = Junk_Chest
        }
    },
    // Cloudy Domain
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 20,
            .trigger_index = 243,
            .type = Junk_Chest
        }
    },
    // Frostbite Village
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 232,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 31,
            .trigger_index = 485,
            .type = Junk_Chest
        }
    },
    // Gloomy Glacier
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 35,
            .trigger_index = 249,
            .type = Junk_Chest
        }
    },
    // Ice Citadel
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 286,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 300,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 309,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 33,
            .trigger_index = 377,
            .type = Junk_Chest
        }
    },
    // Stormy Beach
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 97,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 105,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 168,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 198,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 44,
            .trigger_index = 199,
            .type = Junk_Chest
        }
    },
    // Molten Mount
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 213,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 214,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 215,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 60,
            .trigger_index = 325,
            .type = Junk_Chest
        }
    },
    // Magma Falls Top
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 61,
            .trigger_index = 39,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 61,
            .trigger_index = 49,
            .type = Junk_Chest
        }
    },
    // Magma Falls Bottom
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 63,
            .trigger_index = 51,
            .type = Junk_Chest
        }
    },
    // Dark Mine
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 150,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 211,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 30,
            .trigger_index = 377,
            .type = Junk_Chest
        }
    },
    // Red's Laboratory
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 389,
            .type = Junk_Chest
        }
    },
    {
        .union_type = APC_Grabbable,
        .grabbable = {
            .map_index = 40,
            .trigger_index = 390,
            .type = Junk_Chest
        }
    },
    #pragma endregion
};