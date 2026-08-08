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
			// This is an objective
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
			// This is a grabbable
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
		.objective = 0xFFFF,
        .x = -687.673f,
        .z = 59.447f
	},
	{
		.type = LightGem,
		.map_index = 19,
		.trig_index = 2,
		.objective = 0xFFFF,
        .x = -906.078f,
        .z = -148.267f
	},
	{
		.type = DragonEgg,
		.map_index = 19,
		.trig_index = 3,
		.objective = 0xFFFF,
        .x = -790.679f,
        .z = -43.671f
	},
	{
		.type = DarkGem,
		.map_index = 19,
		.trig_index = 4,
		.objective = 0xFFFF,
        .x = -631.413f,
        .z = 61.091f
	},
	{
		.type = DarkGem,
		.map_index = 19,
		.trig_index = 10,
		.objective = 0xFFFF,
        .x = -732.583f,
        .z = -165.004f
	},
	{
		.type = DragonEgg,
		.map_index = 19,
		.trig_index = 26,
		.objective = 0xFFFF,
        .x = -629.449f,
        .z = 34.074f
	},
	{
		.type = DarkGem,
		.map_index = 19,
		.trig_index = 64,
		.objective = 0xFFFF,
        .x = -604.580f,
        .z = -108.185f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 19,
		.trig_index = 86,
		.objective = 0xFFFF,
        .x = -547.007f,
        .z = 56.702f
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 90,
		.objective = 0xFFFF,
        .x = -633.089f,
        .z = 88.784f
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 91,
		.objective = 0xFFFF,
        .x = -625.657f,
        .z = 158.848f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 19,
		.trig_index = 92,
		.objective = 0xFFFF,
        .x = -891.616f,
        .z = -58.909f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 19,
		.trig_index = 93,
		.objective = 0xFFFF,
        .x = -799.010f,
        .z = -159.200f
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 94,
		.objective = 0xFFFF,
        .x = -496.219f,
        .z = -101.822f
	},
	{
		.type = LightGem,
		.map_index = 19,
		.trig_index = 131,
		.objective = 0xFFFF,
        .x = -762.908f,
        .z = -179.793f
	},
	{
		.type = LightGem_Chest,
		.map_index = 19,
		.trig_index = 183,
		.objective = 0xFFFF,
        .x = -636.020f,
        .z = -82.516f
	},
    #pragma endregion
	#pragma region 20 Cloudy Domain
    {
		.type = DarkGem,
		.map_index = 20,
		.trig_index = 2,
		.objective = 0xFFFF,
        .x = 88.407f,
        .z = 0.269f
	},
	{
		.type = DarkGem,
		.map_index = 20,
		.trig_index = 8,
		.objective = 0xFFFF,
        .x = 391.447f,
        .z = 0.860f
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 9,
		.objective = 0xFFFF,
        .x = 443.121f,
        .z = -89.370f
	},
	{
		.type = DarkGem,
		.map_index = 20,
		.trig_index = 82,
		.objective = 0xFFFF,
        .x = 284.615f,
        .z = -95.921f
	},
	{
		.type = LightGem_Chest,
		.map_index = 20,
		.trig_index = 109,
		.objective = 0xFFFF,
        .x = -51.165f,
        .z = -8.013f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 20,
		.trig_index = 132,
		.objective = 0xFFFF,
        .x = 238.131f,
        .z = -57.230f
	},
	{
		.type = DragonEgg,
		.map_index = 20,
		.trig_index = 133,
		.objective = 0xFFFF,
        .x = 234.517f,
        .z = 70.687f
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 134,
		.objective = 0xFFFF,
        .x = 267.308f,
        .z = 99.230f
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 135,
		.objective = 0xFFFF,
        .x = 191.110f,
        .z = 4.020f
	},
	{
		.type = DragonEgg,
		.map_index = 20,
		.trig_index = 136,
		.objective = 0xFFFF,
        .x = 40.644f,
        .z = -104.773f
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 137,
		.objective = 0xFFFF,
        .x = -181.482f,
        .z = -132.520f
	},
	{
		.type = LightGem,
		.map_index = 20,
		.trig_index = 183,
		.objective = 0xFFFF,
        .x = -4.772f,
        .z = 104.976f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 20,
		.trig_index = 194,
		.objective = 0xFFFF,
        .x = -80.542f,
        .z = 117.823f
	},
	{
		.type = EggThief,
		.map_index = 20,
		.trig_index = 239,
		.objective = 0xFFFF,
        .x = 183.855f,
        .z = -351.459f
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
		.objective = 0xFFFF,
        .x = 709.432f,
        .z = -410.398f
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 11,
		.objective = 0xFFFF,
        .x = 675.898f,
        .z = -296.257f
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 12,
		.objective = 0xFFFF,
        .x = 938.631f,
        .z = -407.264f
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 14,
		.objective = 0xFFFF,
        .x = 680.723f,
        .z = -344.604f
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 15,
		.objective = 0xFFFF,
        .x = 1062.884f,
        .z = -400.652f
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 21,
		.objective = 0xFFFF,
        .x = 1007.291f,
        .z = -589.001f
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 23,
		.objective = 0xFFFF,
        .x = 1296.417f,
        .z = -228.452f
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 29,
		.objective = 0xFFFF,
        .x = 972.379f,
        .z = -669.891f
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 37,
		.objective = 0xFFFF,
        .x = 743.213f,
        .z = -601.936f
	},
	{
		.type = DarkGem,
		.map_index = 22,
		.trig_index = 38,
		.objective = 0xFFFF,
        .x = 846.709f,
        .z = -568.009f
	},
	{
		.type = EggThief,
		.map_index = 22,
		.trig_index = 52,
		.objective = 0xFFFF,
        .x = 1250.741f,
        .z = -308.750f
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 73,
		.objective = 0xFFFF,
        .x = 780.287f,
        .z = -771.342f
	},
	{
		.type = DragonEgg,
		.map_index = 22,
		.trig_index = 74,
		.objective = 0xFFFF,
        .x = 698.026f,
        .z = -797.890f
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 90,
		.objective = 0xFFFF,
        .x = 925.533f,
        .z = -649.716f
	},
	{
		.type = LightGem_Chest,
		.map_index = 22,
		.trig_index = 312,
		.objective = 0xFFFF,
        .x = 579.858f,
        .z = -286.488f
	},
	{
		.type = LightGem,
		.map_index = 22,
		.trig_index = 313,
		.objective = 0xFFFF,
        .x = 925.944f,
        .z = -854.214f
	},
	{
		.type = LightGem_Chest,
		.map_index = 22,
		.trig_index = 314,
		.objective = 0xFFFF,
        .x = 1056.308f,
        .z = -791.347f
	},
    #pragma endregion
	#pragma region 23 Crocovile Swamp
    {
		.type = DarkGem,
		.map_index = 23,
		.trig_index = 0,
		.objective = 0xFFFF,
        .x = 8.988f,
        .z = 538.614f
	},
	{
		.type = EggThief,
		.map_index = 23,
		.trig_index = 1,
		.objective = 0xFFFF,
        .x = 293.351f,
        .z = 734.020f
	},
	{
		.type = DarkGem,
		.map_index = 23,
		.trig_index = 5,
		.objective = 0xFFFF,
        .x = 152.106f,
        .z = 537.051f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 8,
		.objective = 0xFFFF,
        .x = 334.059f,
        .z = 619.921f
	},
	{
		.type = DragonEgg,
		.map_index = 23,
		.trig_index = 36,
		.objective = 0xFFFF,
        .x = 207.287f,
        .z = 509.651f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 48,
		.objective = 0xFFFF,
        .x = 297.543f,
        .z = 592.444f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 49,
		.objective = 0xFFFF,
        .x = 105.845f,
        .z = 594.520f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 54,
		.objective = 0xFFFF,
        .x = 165.745f,
        .z = 750.651f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 58,
		.objective = 0xFFFF,
        .x = 75.439f,
        .z = 538.957f
	},
	{
		.type = DragonEgg,
		.map_index = 23,
		.trig_index = 62,
		.objective = 0xFFFF,
        .x = -151.165f,
        .z = 491.431f
	},
	{
		.type = DarkGem,
		.map_index = 23,
		.trig_index = 68,
		.objective = 0xFFFF,
        .x = 175.806f,
        .z = 482.756f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 23,
		.trig_index = 103,
		.objective = 0xFFFF,
        .x = 135.360f,
        .z = 593.936f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 161,
		.objective = 0xFFFF,
        .x = 73.546f,
        .z = 549.902f
	},
	{
		.type = LightGem_Chest,
		.map_index = 23,
		.trig_index = 162,
		.objective = 0xFFFF,
        .x = -58.559f,
        .z = 515.100f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 23,
		.trig_index = 202,
		.objective = 0xFFFF,
        .x = 171.311f,
        .z = 659.408f
	},
	{
		.type = DragonEgg,
		.map_index = 23,
		.trig_index = 203,
		.objective = 0xFFFF,
        .x = 287.616f,
        .z = 506.183f
	},
	{
		.type = LightGem,
		.map_index = 23,
		.trig_index = 204,
		.objective = 0xFFFF,
        .x = 193.263f,
        .z = 508.721f
	},
    #pragma endregion
	#pragma region 24 Dragon Village
    {
		.type = DarkGem,
		.map_index = 24,
		.trig_index = 1,
		.objective = 0xFFFF,
        .x = 87.140f,
        .z = 62.445f
	},
	{
		.type = DarkGem,
		.map_index = 24,
		.trig_index = 2,
		.objective = 0xFFFF,
        .x = 228.663f,
        .z = 69.036f
	},
	{
		.type = DarkGem,
		.map_index = 24,
		.trig_index = 8,
		.objective = 0xFFFF,
        .x = -107.383f,
        .z = -8.333f
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 16,
		.objective = 0xFFFF,
        .x = -106.383f,
        .z = 8.255f
	},
	{
		.type = LightGem,
		.map_index = 24,
		.trig_index = 21,
		.objective = 0xFFFF,
        .x = -67.898f,
        .z = -83.488f
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 92,
		.objective = 0xFFFF,
        .x = 384.315f,
        .z = -25.722f
	},
	{
		.type = LightGem,
		.map_index = 24,
		.trig_index = 139,
		.objective = 0xFFFF,
        .x = 45.001f,
        .z = -102.361f
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 141,
		.objective = 0xFFFF,
        .x = 12.535f,
        .z = -75.268f
	},
	{
		.type = LightGem,
		.map_index = 24,
		.trig_index = 290,
		.objective = 0xFFFF,
        .x = 182.639f,
        .z = -11.277f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 24,
		.trig_index = 302,
		.objective = 0xFFFF,
        .x = 200.086f,
        .z = -8.877f
	},
	{
		.type = DragonEgg,
		.map_index = 24,
		.trig_index = 341,
		.objective = 0xFFFF,
        .x = 202.560f,
        .z = -165.061f
	},
	{
		.type = LightGem_Chest,
		.map_index = 24,
		.trig_index = 342,
		.objective = 0xFFFF,
        .x = 35.483f,
        .z = -44.351f
	},
	{
		.type = LightGem_Chest,
		.map_index = 24,
		.trig_index = 343,
		.objective = 0xFFFF,
        .x = 66.002f,
        .z = 159.513f
	},
    #pragma endregion
    #pragma region 30 Dark Mine
	{
		.type = DarkGem,
		.map_index = 30,
		.trig_index = 19,
		.objective = 0xFFFF,
        .x = -392.190f,
        .z = -1620.263f
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 83,
		.objective = 0xFFFF,
        .x = -701.032f,
        .z = -1398.659f
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 84,
		.objective = 0xFFFF,
        .x = -487.318f,
        .z = -1565.012f
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 85,
		.objective = 0xFFFF,
        .x = -671.799f,
        .z = -1623.578f
	},
	{
		.type = LightGem,
		.map_index = 30,
		.trig_index = 86,
		.objective = 0xFFFF,
        .x = -514.328f,
        .z = -1702.092f
	},
	{
		.type = DragonEgg,
		.map_index = 30,
		.trig_index = 87,
		.objective = 0xFFFF,
        .x = -635.657f,
        .z = -1405.647f
	},
	{
		.type = DragonEgg,
		.map_index = 30,
		.trig_index = 88,
		.objective = 0xFFFF,
        .x = -575.873f,
        .z = -1707.055f
	},
	{
		.type = DarkGem,
		.map_index = 30,
		.trig_index = 89,
		.objective = 0xFFFF,
        .x = -598.073f,
        .z = -1628.077f
	},
	{
		.type = LightGem_Chest,
		.map_index = 30,
		.trig_index = 150,
		.objective = 0xFFFF,
        .x = -432.978f,
        .z = -1487.420f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 30,
		.trig_index = 211,
		.objective = 0xFFFF,
        .x = -524.919f,
        .z = -1531.056f
	},
	{
		.type = DragonEgg,
		.map_index = 30,
		.trig_index = 214,
		.objective = 0xFFFF,
        .x = -375.168f,
        .z = -1719.951f
	},
    #pragma endregion
    #pragma region 31 Frostbite Village
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 4,
		.objective = 0xFFFF,
        .x = -163.103f,
        .z = 135.544f
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 5,
		.objective = 0xFFFF,
        .x = 60.377f,
        .z = 147.530f
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 6,
		.objective = 0xFFFF,
        .x = 188.558f,
        .z = 86.418f
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 7,
		.objective = 0xFFFF,
        .x = 235.793f,
        .z = 35.055f
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 11,
		.objective = 0xFFFF,
        .x = 277.068f,
        .z = -445.761f
	},
	{
		.type = DragonEgg,
		.map_index = 31,
		.trig_index = 36,
		.objective = 0xFFFF,
        .x = -106.951f,
        .z = 96.723f
	},
	{
		.type = EggThief,
		.map_index = 31,
		.trig_index = 60,
		.objective = 0xFFFF,
        .x = 293.786f,
        .z = -178.487f
	},
	{
		.type = DragonEgg,
		.map_index = 31,
		.trig_index = 61,
		.objective = 0xFFFF,
        .x = 250.211f,
        .z = -350.799f
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 66,
		.objective = 0xFFFF,
        .x = 266.501f,
        .z = -478.457f
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 74,
		.objective = 0xFFFF,
        .x = 296.465f,
        .z = -275.830f
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 150,
		.objective = 0xFFFF,
        .x = -119.191f,
        .z = -24.916f
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 170,
		.objective = 0xFFFF,
        .x = 69.112f,
        .z = 307.069f
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 246,
		.objective = 0xFFFF,
        .x = -97.852f,
        .z = 165.881f
	},
	{
		.type = DarkGem,
		.map_index = 31,
		.trig_index = 247,
		.objective = 0xFFFF,
        .x = 75.265f,
        .z = -158.639f
	},
	{
		.type = LightGem,
		.map_index = 31,
		.trig_index = 312,
		.objective = 0xFFFF,
        .x = -21.688f,
        .z = -470.546f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 31,
		.trig_index = 372,
		.objective = 0xFFFF,
        .x = 57.459f,
        .z = 264.138f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 31,
		.trig_index = 373,
		.objective = 0xFFFF,
        .x = 114.466f,
        .z = 69.870f
	},
    #pragma endregion
    #pragma region 33 Ice Citadel
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 4,
		.objective = 0xFFFF,
        .x = -796.231f,
        .z = -326.562f
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 8,
		.objective = 0xFFFF,
        .x = -707.511f,
        .z = -152.005f
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 11,
		.objective = 0xFFFF,
        .x = -546.610f,
        .z = -154.257f
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 15,
		.objective = 0xFFFF,
        .x = -589.098f,
        .z = -189.818f
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 21,
		.objective = 0xFFFF,
        .x = -386.851f,
        .z = -125.771f
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 22,
		.objective = 0xFFFF,
        .x = -421.771f,
        .z = -113.849f
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 31,
		.objective = 0xFFFF,
        .x = -639.206f,
        .z = -364.310f
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 33,
		.objective = 0xFFFF,
        .x = -594.839f,
        .z = -288.317f
	},
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 36,
		.objective = 0xFFFF,
        .x = -626.585f,
        .z = -290.399f
	},
	{
		.type = DarkGem,
		.map_index = 33,
		.trig_index = 44,
		.objective = 0xFFFF,
        .x = -546.963f,
        .z = -417.671f
	},
	{
		.type = DragonEgg,
		.map_index = 33,
		.trig_index = 45,
		.objective = 0xFFFF,
        .x = -615.706f,
        .z = -458.546f
	},
	{
		.type = LightGem_Chest,
		.map_index = 33,
		.trig_index = 67,
		.objective = 0xFFFF,
        .x = -670.845f,
        .z = -173.750f
	},
	{
		.type = EggThief,
		.map_index = 33,
		.trig_index = 133,
		.objective = 0xFFFF,
        .x = -330.000f,
        .z = -80.000f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 33,
		.trig_index = 421,
		.objective = 0xFFFF,
        .x = -773.415f,
        .z = -108.710f
	},
    #pragma endregion
    #pragma region 35 Gloomy Glacier
	{
		.type = DragonEgg,
		.map_index = 35,
		.trig_index = 1,
		.objective = 0xFFFF,
        .x = 187.602f,
        .z = -716.696f
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 2,
		.objective = 0xFFFF,
        .x = 77.346f,
        .z = -790.991f
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 15,
		.objective = 0xFFFF,
        .x = 336.983f,
        .z = -913.114f
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 27,
		.objective = 0xFFFF,
        .x = 68.165f,
        .z = -1400.024f
	},
	{
		.type = DragonEgg,
		.map_index = 35,
		.trig_index = 57,
		.objective = 0xFFFF,
        .x = 194.297f,
        .z = -1429.799f
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 58,
		.objective = 0xFFFF,
        .x = 84.155f,
        .z = -1311.049f
	},
	{
		.type = DragonEgg,
		.map_index = 35,
		.trig_index = 212,
		.objective = 0xFFFF,
        .x = 280.546f,
        .z = -1022.916f
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 232,
		.objective = 0xFFFF,
        .x = 231.672f,
        .z = -1394.083f
	},
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 233,
		.objective = 0xFFFF,
        .x = 210.635f,
        .z = -1273.260f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 35,
		.trig_index = 267,
		.objective = 0xFFFF,
        .x = 126.942f,
        .z = -817.064f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 35,
		.trig_index = 268,
		.objective = 0xFFFF,
        .x = 317.489f,
        .z = -585.642f
	},
    #pragma endregion
    #pragma region 40 Reds Laboratory
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 1,
		.objective = 0xFFFF,
        .x = -1070.981f,
        .z = -1205.956f
	},
	{
		.type = DarkGem,
		.map_index = 40,
		.trig_index = 2,
		.objective = 0xFFFF,
        .x = -1597.688f,
        .z = -1304.058f
	},
	{
		.type = DarkGem,
		.map_index = 40,
		.trig_index = 3,
		.objective = 0xFFFF,
        .x = -957.165f,
        .z = -1200.406f
	},
	{
		.type = DarkGem,
		.map_index = 40,
		.trig_index = 4,
		.objective = 0xFFFF,
        .x = -1069.976f,
        .z = -1617.574f
	},
	{
		.type = DragonEgg,
		.map_index = 40,
		.trig_index = 41,
		.objective = 0xFFFF,
        .x = -1350.317f,
        .z = -1317.104f
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 109,
		.objective = 0xFFFF,
        .x = -1142.621f,
        .z = -1473.406f
	},
	{
		.type = DragonEgg,
		.map_index = 40,
		.trig_index = 110,
		.objective = 0xFFFF,
        .x = -975.346f,
        .z = -1607.982f
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 111,
		.objective = 0xFFFF,
        .x = -990.302f,
        .z = -1540.030f
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 115,
		.objective = 0xFFFF,
        .x = -1441.266f,
        .z = -1354.549f
	},
	{
		.type = EggThief,
		.map_index = 40,
		.trig_index = 237,
		.objective = 0xFFFF,
        .x = -1241.792f,
        .z = -1420.346f
	},
	{
		.type = LightGem,
		.map_index = 40,
		.trig_index = 388,
		.objective = 0xFFFF,
        .x = -1514.395f,
        .z = -1282.014f
	},
    #pragma endregion
    #pragma region 44 Stormy Beach
	{
		.type = DarkGem,
		.map_index = 44,
		.trig_index = 27,
		.objective = 0xFFFF,
        .x = -92.003f,
        .z = 303.808f
	},
	{
		.type = LightGem,
		.map_index = 44,
		.trig_index = 44,
		.objective = 0xFFFF,
        .x = -213.556f,
        .z = 57.555f
	},
	{
		.type = EggThief,
		.map_index = 44,
		.trig_index = 66,
		.objective = 0xFFFF,
        .x = -34.484f,
        .z = 18.496f
	},
    #pragma endregion
    #pragma region 45 Coastal Remains
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 0,
		.objective = 0xFFFF,
        .x = -115.731f,
        .z = -226.261f
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 2,
		.objective = 0xFFFF,
        .x = 132.225f,
        .z = -92.283f
	},
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 3,
		.objective = 0xFFFF,
        .x = 207.902f,
        .z = -146.365f
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 4,
		.objective = 0xFFFF,
        .x = 78.532f,
        .z = -206.129f
	},
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 7,
		.objective = 0xFFFF,
        .x = 99.567f,
        .z = 162.294f
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 11,
		.objective = 0xFFFF,
        .x = -184.912f,
        .z = 59.219f
	},
	{
		.type = DragonEgg,
		.map_index = 45,
		.trig_index = 12,
		.objective = 0xFFFF,
        .x = -101.286f,
        .z = -36.468f
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 13,
		.objective = 0xFFFF,
        .x = -236.195f,
        .z = -67.429f
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 19,
		.objective = 0xFFFF,
        .x = 380.275f,
        .z = -35.876f
	},
	{
		.type = DarkGem,
		.map_index = 45,
		.trig_index = 29,
		.objective = 0xFFFF,
        .x = -435.760f,
        .z = -95.785f
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 47,
		.objective = 0xFFFF,
        .x = 342.804f,
        .z = -39.804f
	},
	{
		.type = EggThief,
		.map_index = 45,
		.trig_index = 59,
		.objective = 0xFFFF,
        .x = 305.556f,
        .z = 98.605f
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 119,
		.objective = 0xFFFF,
        .x = 398.746f,
        .z = 110.269f
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 120,
		.objective = 0xFFFF,
        .x = -26.176f,
        .z = -204.344f
	},
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 192,
		.objective = 0xFFFF,
        .x = -446.493f,
        .z = 32.213f
	},
    #pragma endregion
    #pragma region 60 Molten Mount
	{
		.type = LightGem,
		.map_index = 60,
		.trig_index = 4,
		.objective = 0xFFFF,
        .x = -145.076f,
        .z = 855.619f
	},
	{
		.type = LightGem,
		.map_index = 60,
		.trig_index = 5,
		.objective = 0xFFFF,
        .x = -149.880f,
        .z = 1027.325f
	},
	{
		.type = DragonEgg,
		.map_index = 60,
		.trig_index = 6,
		.objective = 0xFFFF,
        .x = -267.886f,
        .z = 651.690f
	},
	{
		.type = DarkGem,
		.map_index = 60,
		.trig_index = 9,
		.objective = 0xFFFF,
        .x = 93.966f,
        .z = 1114.592f
	},
	{
		.type = LightGem,
		.map_index = 60,
		.trig_index = 17,
		.objective = 0xFFFF,
        .x = 157.400f,
        .z = 1252.836f
	},
	{
		.type = DarkGem,
		.map_index = 60,
		.trig_index = 21,
		.objective = 0xFFFF,
        .x = 167.944f,
        .z = 985.603f
	},
	{
		.type = EggThief,
		.map_index = 60,
		.trig_index = 36,
		.objective = 0xFFFF,
        .x = 347.688f,
        .z = 1164.352f
	},
	{
		.type = DarkGem,
		.map_index = 60,
		.trig_index = 63,
		.objective = 0xFFFF,
        .x = -163.745f,
        .z = 610.811f
	},
	{
		.type = LightGem_Chest,
		.map_index = 60,
		.trig_index = 213,
		.objective = 0xFFFF,
        .x = -213.884f,
        .z = 562.944f
	},
	{
		.type = DragonEgg_Chest,
		.map_index = 60,
		.trig_index = 214,
		.objective = 0xFFFF,
        .x = 185.123f,
        .z = 920.068f
	},
	{
		.type = LightGem_Chest,
		.map_index = 60,
		.trig_index = 215,
		.objective = 0xFFFF,
        .x = 309.684f,
        .z = 939.061f
	},
    #pragma endregion
    #pragma region 61 Magma Falls Top
	{
		.type = DragonEgg_Chest,
		.map_index = 61,
		.trig_index = 39,
		.objective = 0xFFFF,
        .x = 286.530f,
        .z = 863.705f
	},
	{
		.type = LightGem,
		.map_index = 61,
		.trig_index = 57,
		.objective = 0xFFFF,
        .x = 196.759f,
        .z = 834.204f
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
		.objective = 0xFFFF,
        .x = 135.064f,
        .z = -1068.570f
	},
	{
		.type = EggThief,
		.map_index = 63,
		.trig_index = 10,
		.objective = 0xFFFF,
        .x = -237.019f,
        .z = -1036.122f
	},
	{
		.type = LightGem,
		.map_index = 63,
		.trig_index = 16,
		.objective = 0xFFFF,
        .x = -82.247f,
        .z = -1162.160f
	},
	{
		.type = LightGem_Chest,
		.map_index = 63,
		.trig_index = 51,
		.objective = 0xFFFF,
        .x = 29.596f,
        .z = -1150.912f
	},
    #pragma endregion

    #pragma region Objectives
    // Dragon Village - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 24,
		.trig_index = 158,
		.objective = HT_Objective_MR1_HalfDone & 0xFFFF,
        .x = -101.334f,
        .z = -55.373f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 24,
		.trig_index = 158,
		.objective = HT_Objective_MR1_AllDone & 0xFFFF,
        .x = -101.334f,
        .z = -55.373f
	},
    // Crocovile Swamp - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 23,
		.trig_index = 6,
		.objective = HT_Objective_MR1_Spy_HalfDone & 0xFFFF,
        .x = 144.060f,
        .z = 578.149f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 23,
		.trig_index = 6,
		.objective = HT_Objective_MiniGame1A_Complete & 0xFFFF,
        .x = 144.060f,
        .z = 578.149f
	},
    // Crocovile Swamp - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 23,
		.trig_index = 69,
		.objective = HT_Objective_MR1_Blk_HalfDone & 0xFFFF,
        .x = 225.391f,
        .z = 524.413f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 23,
		.trig_index = 69,
		.objective = HT_Objective_MR1_Blk_AllDone & 0xFFFF,
        .x = 225.391f,
        .z = 524.413f
	},
    // Dragonfly Falls - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 22,
		.trig_index = 283,
		.objective = HT_Objective_MR1_Spx_Egg & 0xFFFF,
        .x = 1115.686f,
        .z = -576.150f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 22,
		.trig_index = 283,
		.objective = HT_Objective_MR1_Spx_AllDone & 0xFFFF,
        .x = 1115.686f,
        .z = -576.150f
	},
    // Coastal Remains - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 45,
		.trig_index = 115,
		.objective = HT_Objective_MR2_Blk_HalfDone & 0xFFFF,
        .x = -262.141f,
        .z = -86.490f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 45,
		.trig_index = 115,
		.objective = HT_Objective_MR2_Blk_AllDone & 0xFFFF,
        .x = -262.141f,
        .z = -86.490f
	},
    // Coastal Remains - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 45,
		.trig_index = 77,
		.objective = HT_Objective_MR2_Spy_HalfDone & 0xFFFF,
        .x = -159.896f,
        .z = -236.013f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 45,
		.trig_index = 77,
		.objective = HT_Objective_MR2_Spy_AllDone & 0xFFFF,
        .x = -159.896f,
        .z = -236.013f
	},
    // Coastal Remains - Otto
	{
		.type = LightGem,
		.map_index = 45,
		.trig_index = 150,
		.objective = HT_Objective_OtterNPC_AllDone & 0xFFFF,
        .x = -135.012f,
        .z = 26.804f
	},
    // Sunken Ruins - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 19,
		.trig_index = 65,
		.objective = HT_Objective_MR2_Spx_HalfDone & 0xFFFF,
        .x = -842.878f,
        .z = -44.993f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 19,
		.trig_index = 65,
		.objective = HT_Objective_MR2_Spx_AllDone & 0xFFFF,
        .x = -842.878f,
        .z = -44.993f
	},
    // Cloudy Domain - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 20,
		.trig_index = 81,
		.objective = HT_Objective_MR2_Sgt_HalfDone & 0xFFFF,
        .x = 380.287f,
        .z = -125.903f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 20,
		.trig_index = 81,
		.objective = HT_Objective_MR2_Sgt_AllDone & 0xFFFF,
        .x = 380.287f,
        .z = -125.903f
	},
    // Frostbite Village - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 31,
		.trig_index = 244,
		.objective = HT_Objective_MR3_Blk_HalfDone & 0xFFFF,
        .x = 28.673f,
        .z = -178.357f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 31,
		.trig_index = 244,
		.objective = HT_Objective_MR3_Blk_AllDone & 0xFFFF,
        .x = 28.673f,
        .z = -178.357f
	},
    // Frostbite Village - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 31,
		.trig_index = 242,
		.objective = HT_Objective_MR3_Spy_HalfDone & 0xFFFF,
        .x = -83.802f,
        .z = 100.301f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 31,
		.trig_index = 242,
		.objective = HT_Objective_MR3_Spy_AllDone & 0xFFFF,
        .x = -83.802f,
        .z = 100.301f
	},
    // Gloomy Glacier - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 35,
		.trig_index = 128,
		.objective = HT_Objective_MR3_Spx_HalfDone & 0xFFFF,
        .x = 142.240f,
        .z = -1387.189f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 35,
		.trig_index = 128,
		.objective = HT_Objective_MR3_Spx_AllDone & 0xFFFF,
        .x = 142.240f,
        .z = -1387.189f
	},
    // Gloomy Glacier - Bentley
	{
		.type = LightGem,
		.map_index = 35,
		.trig_index = 88,
		.objective = HT_Objective_3B_BentleyHasRewarded & 0xFFFF,
        .x = 65.178f,
        .z = -615.165f
	},
    // Ice Citadel - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 33,
		.trig_index = 48,
		.objective = HT_Objective_MR3_Sgt_HalfDone & 0xFFFF,
        .x = -448.719f,
        .z = -173.292f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 33,
		.trig_index = 48,
		.objective = HT_Objective_MR3_Sgt_AllDone & 0xFFFF,
        .x = -448.719f,
        .z = -173.292f
	},
    // Ice Citadel - Boiler 1
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 97,
		.objective = HT_Objective_3C_LitBoiler_1 & 0xFFFF,
        .x = -413.696f,
        .z = -235.004f
	},
    // Ice Citadel - Boiler 3
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 99,
		.objective = HT_Objective_3C_LitBoiler_3 & 0xFFFF,
        .x = -709.677f,
        .z = -249.536f
	},
    // Ice Citadel - Boiler 5
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 101,
		.objective = HT_Objective_3C_LitBoiler_5 & 0xFFFF,
        .x = -855.619f,
        .z = -325.652f
	},
    // Ice Citadel - Ice Princess
	{
		.type = LightGem,
		.map_index = 33,
		.trig_index = 47,
		.objective = HT_Objective_3C_IcePrincessHasRewarded & 0xFFFF,
        .x = -494.835f,
        .z = -340.113f
	},
    // Stormy Beach - Turret
	{
		.type = DragonEgg_MiniGame,
		.map_index = 44,
		.trig_index = 8,
		.objective = HT_Objective_MR4_Spy_HalfDone & 0xFFFF,
        .x = 110.059f,
        .z = -41.345f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 44,
		.trig_index = 8,
		.objective = HT_Objective_MR4_Spy_AllDone & 0xFFFF,
        .x = 110.059f,
        .z = -41.345f
	},
    // Molten Mount - Sgt. Byrd
	{
		.type = DragonEgg_MiniGame,
		.map_index = 60,
		.trig_index = 94,
		.objective = HT_Objective_MR4_Sgt_HalfDone & 0xFFFF,
        .x = -226.573f,
        .z = 552.857f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 60,
		.trig_index = 94,
		.objective = HT_Objective_MR4_Sgt_AllDone & 0xFFFF,
        .x = -226.573f,
        .z = 552.857f
	},
    // Molten Mount - Teena
	{
		.type = DragonEgg,
		.map_index = 60,
		.trig_index = 93,
		.objective = HT_Objective_TeenaHasRewarded & 0xFFFF,
        .x = 8.892f,
        .z = 620.573f
	},
    // Magma Falls Bottom - Sparx
	{
		.type = DragonEgg_MiniGame,
		.map_index = 63,
		.trig_index = 12,
		.objective = HT_Objective_MR4_Spx_HalfDone & 0xFFFF,
        .x = -170.275f,
        .z = -1263.319f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 63,
		.trig_index = 12,
		.objective = HT_Objective_MR4_Spx_AllDone & 0xFFFF,
        .x = -170.275f,
        .z = -1263.319f
	},
    // Dark Mine - Blink
	{
		.type = DragonEgg_MiniGame,
		.map_index = 30,
		.trig_index = 154,
		.objective = HT_Objective_MR4_Blk_HalfDone & 0xFFFF,
        .x = -366.247f,
        .z = -1674.918f
	},
	{
		.type = LightGem_MiniGame,
		.map_index = 30,
		.trig_index = 154,
		.objective = HT_Objective_MR4_Blk_AllDone & 0xFFFF,
        .x = -366.247f,
        .z = -1674.918f
	},
    #pragma endregion

    #pragma region Junk Chests
    // Coastal Remains
	{
		.type = Junk_Chest,
		.map_index = 45,
		.trig_index = 315,
		.objective = 0xFFFF,
        .x = 62.367f,
        .z = -147.963f
	},
	{
		.type = Junk_Chest,
		.map_index = 45,
		.trig_index = 462,
		.objective = 0xFFFF,
        .x = 55.209f,
        .z = 29.594f
	},
    // Sunken Ruins
	{
		.type = Junk_Chest,
		.map_index = 19,
		.trig_index = 284,
		.objective = 0xFFFF,
        .x = -521.021f,
        .z = -25.964f
	},
    // Cloudy Domain
	{
		.type = Junk_Chest,
		.map_index = 20,
		.trig_index = 243,
		.objective = 0xFFFF,
        .x = 377.338f,
        .z = 126.372f
	},
    // Frostbite Village
	{
		.type = Junk_Chest,
		.map_index = 31,
		.trig_index = 232,
		.objective = 0xFFFF,
        .x = 224.375f,
        .z = 57.598f
	},
	{
		.type = Junk_Chest,
		.map_index = 31,
		.trig_index = 485,
		.objective = 0xFFFF,
        .x = -89.514f,
        .z = 74.633f
	},
    // Gloomy Glacier
	{
		.type = Junk_Chest,
		.map_index = 35,
		.trig_index = 249,
		.objective = 0xFFFF,
        .x = 265.841f,
        .z = -596.061f
	},
    // Ice Citadel
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 286,
		.objective = 0xFFFF,
        .x = -511.801f,
        .z = -174.690f
	},
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 300,
		.objective = 0xFFFF,
        .x = -448.911f,
        .z = -125.507f
	},
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 309,
		.objective = 0xFFFF,
        .x = -511.236f,
        .z = -328.987f
	},
	{
		.type = Junk_Chest,
		.map_index = 33,
		.trig_index = 377,
		.objective = 0xFFFF,
        .x = -743.205f,
        .z = -407.357f
	},
    // Stormy Beach
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 97,
		.objective = 0xFFFF,
        .x = -26.082f,
        .z = 197.565f
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 105,
		.objective = 0xFFFF,
        .x = 85.674f,
        .z = -85.783f
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 168,
		.objective = 0xFFFF,
        .x = -240.171f,
        .z = -49.765f
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 198,
		.objective = 0xFFFF,
        .x = -157.695f,
        .z = 38.666f
	},
	{
		.type = Junk_Chest,
		.map_index = 44,
		.trig_index = 199,
		.objective = 0xFFFF,
        .x = 9.642f,
        .z = 161.055f
	},
    // Molten Mount
	{
		.type = Junk_Chest,
		.map_index = 60,
		.trig_index = 325,
		.objective = 0xFFFF,
        .x = 301.385f,
        .z = 1208.420f
	},
    // Magma Falls Top
	{
		.type = Junk_Chest,
		.map_index = 61,
		.trig_index = 49,
		.objective = 0xFFFF,
        .x = 225.428f,
        .z = 895.251f
	},
    // Dark Mine
	{
		.type = Junk_Chest,
		.map_index = 30,
		.trig_index = 377,
		.objective = 0xFFFF,
        .x = -497.835f,
        .z = -1427.931f
	},
    // Red's Laboratory
	{
		.type = Junk_Chest,
		.map_index = 40,
		.trig_index = 389,
		.objective = 0xFFFF,
        .x = -1022.593f,
        .z = -1403.821f
	},
	{
		.type = Junk_Chest,
		.map_index = 40,
		.trig_index = 390,
		.objective = 0xFFFF,
        .x = -1077.671f,
        .z = -1372.523f
	},
    #pragma endregion

    #pragma region Dragon Elders
    // Elder Tomas
	{
		.type = NonCollectable,
		.map_index = 24,
		.trig_index = 11,
		.objective = 0x1,
        .x = 206.557f,
        .z = 54.382f
	},
    // Elder Magnus
	{
		.type = NonCollectable,
		.map_index = 23,
		.trig_index = 71,
		.objective = 0x3,
        .x = 181.836f,
        .z = 503.226f
	},
    // Elder Titan
	{
		.type = NonCollectable,
		.map_index = 20,
		.trig_index = 10,
		.objective = 0x9d,
        .x = 240.131f,
        .z = -0.156f
	},
    // Elder Astor
	{
		.type = NonCollectable,
		.map_index = 33,
		.trig_index = 9,
		.objective = 0x9c,
        .x = -682.961f,
        .z = -148.253f
	},
    #pragma endregion

    #pragma region Bosses
    // Gnasty Gnorc
	{
		.type = NonCollectable,
		.map_index = 24,
		.trig_index = 346,
		.objective = 0x81,
        .x = 151.245f,
        .z = -102.081f
	},
    // Ineptune
	{
		.type = NonCollectable,
		.map_index = 45,
		.trig_index = 235,
		.objective = 0x82,
        .x = 3.925f,
        .z = 80.844f
	},
    // Red
	{
		.type = NonCollectable,
		.map_index = 31,
		.trig_index = 318,
		.objective = 0x83,
        .x = -51.937f,
        .z = -58.285f
	},
    // Mecha Red
	{
		.type = NonCollectable,
		.map_index = 40,
		.trig_index = 391,
		.objective = 0x84,
        .x = -1281.773f,
        .z = -1668.250f
	},
    #pragma endregion

    #pragma region Fireworks
    // Dragon Village
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 304,
		.objective = 0xFFFF,
        .x = 223.690f,
        .z = -74.603f
	},
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 305,
		.objective = 0xFFFF,
        .x = 292.670f,
        .z = 15.199f
	},
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 344,
		.objective = 0xFFFF,
        .x = 58.806f,
        .z = 133.725f
	},
	{
		.type = FireWork,
		.map_index = 24,
		.trig_index = 431,
		.objective = 0xFFFF,
        .x = -66.573f,
        .z = -70.162f
	},
    // Crocovile Swamp
	{
		.type = FireWork,
		.map_index = 23,
		.trig_index = 276,
		.objective = 0xFFFF,
        .x = 197.835f,
        .z = 495.531f
	},
	{
		.type = FireWork,
		.map_index = 23,
		.trig_index = 292,
		.objective = 0xFFFF,
        .x = -68.490f,
        .z = 443.695f
	},
	{
		.type = FireWork,
		.map_index = 23,
		.trig_index = 294,
		.objective = 0xFFFF,
        .x = 209.934f,
        .z = 496.094f
	},
    // Sunken Ruins
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 207,
		.objective = 0xFFFF,
        .x = -625.890f,
        .z = 81.543f
	},
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 236,
		.objective = 0xFFFF,
        .x = -815.179f,
        .z = -4.108f
	},
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 252,
		.objective = 0xFFFF,
        .x = -802.593f,
        .z = -201.492f
	},
	{
		.type = FireWork,
		.map_index = 19,
		.trig_index = 287,
		.objective = 0xFFFF,
        .x = -590.070f,
        .z = -131.139f
	},
    // Cloudy Domain
	{
		.type = FireWork,
		.map_index = 20,
		.trig_index = 113,
		.objective = 0xFFFF,
        .x = -111.685f,
        .z = 23.601f
	},
	{
		.type = FireWork,
		.map_index = 20,
		.trig_index = 264,
		.objective = 0xFFFF,
        .x = 120.875f,
        .z = -35.000f
	},
	{
		.type = FireWork,
		.map_index = 20,
		.trig_index = 273,
		.objective = 0xFFFF,
        .x = 16.897f,
        .z = 131.332f
	},
    // Ice Citadel
	{
		.type = FireWork,
		.map_index = 33,
		.trig_index = 250,
		.objective = 0xFFFF,
        .x = -822.257f,
        .z = -337.989f
	},
    // Stormy Beach
	{
		.type = FireWork,
		.map_index = 44,
		.trig_index = 98,
		.objective = 0xFFFF,
        .x = -151.700f,
        .z = 64.303f
	},
	{
		.type = FireWork,
		.map_index = 44,
		.trig_index = 113,
		.objective = 0xFFFF,
        .x = 53.333f,
        .z = 42.170f
	},
	{
		.type = FireWork,
		.map_index = 44,
		.trig_index = 149,
		.objective = 0xFFFF,
        .x = -49.664f,
        .z = 177.840f
	},
    // Molten Mount
	{
		.type = FireWork,
		.map_index = 60,
		.trig_index = 132,
		.objective = 0xFFFF,
        .x = -96.888f,
        .z = 551.814f
	},
    // Magma Falls Top
	{
		.type = FireWork,
		.map_index = 61,
		.trig_index = 19,
		.objective = 0xFFFF,
        .x = 194.501f,
        .z = 864.891f
	},
    // Dark Mine
	{
		.type = FireWork,
		.map_index = 30,
		.trig_index = 315,
		.objective = 0xFFFF,
        .x = -488.456f,
        .z = -1539.120f
	},
	{
		.type = FireWork,
		.map_index = 30,
		.trig_index = 366,
		.objective = 0xFFFF,
        .x = -508.205f,
        .z = -1708.773f
	}
    #pragma endregion
};
