#include <ap_triginfo.h>
#include <gamestate.h>
#include <hashcodes.h>

GameStateTrigInfo shops_triginfos[] = {
    // Dragon Village - Village Depot
    {
        .m_MapIndex = 24,
        .m_TrigIndex = 22,
        .m_XYZ = {
            .x = 131.375565f,
            .y = -2.953816f,
            .z = -11.364732f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_MAINSHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1A,
            }
        }
    },
    // Crocovile Swamp - Elder's Tree
    {
        .m_MapIndex = 23,
        .m_TrigIndex = 107,
        .m_XYZ = {
            .x = 197.776062f,
            .y = -23.059521f,
            .z = 471.081818f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1B_02,
            }
        }
    },
    // Crocovile Swamp - Forgotten Temple
    {
        .m_MapIndex = 23,
        .m_TrigIndex = 109,
        .m_XYZ = {
            .x = 169.592377f,
            .y = -21.089113f,
            .z = 626.782654f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1B_03,
            }
        }
    },
    // Crocovile Swamp - Perilous Pyramid
    {
        .m_MapIndex = 23,
        .m_TrigIndex = 137,
        .m_XYZ = {
            .x = 39.919754f,
            .y = -13.149541f,
            .z = 517.287170f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1B_01,
            }
        }
    },
    // Dragonfly Falls - Steep Canyon
    {
        .m_MapIndex = 22,
        .m_TrigIndex = 16,
        .m_XYZ = {
            .x = 645.000000f,
            .y = 14.760874f,
            .z = -445.000000f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1C_01,
            }
        }
    },
    // Dragonfly Falls - Secret Area
    {
        .m_MapIndex = 22,
        .m_TrigIndex = 182,
        .m_XYZ = {
            .x = 1153.867554f,
            .y = 15.348602f,
            .z = -409.769714f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1C_02,
            }
        }
    },
    // Dragonfly Falls - Tropical  Cove
    {
        .m_MapIndex = 22,
        .m_TrigIndex = 290,
        .m_XYZ = {
            .x = 994.407471f,
            .y = -36.903439f,
            .z = -694.421082f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R1C_03,
            }
        }
    },
    // Coastal Remains - Waterfall Walkway
    {
        .m_MapIndex = 45,
        .m_TrigIndex = 32,
        .m_XYZ = {
            .x = -264.341309f,
            .y = -3.638232f,
            .z = -66.575653f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2A_01,
            }
        }
    },
    // Coastal Remains - Domain Doorstep
    {
        .m_MapIndex = 45,
        .m_TrigIndex = 38,
        .m_XYZ = {
            .x = 397.344513f,
            .y = 11.644712f,
            .z = 29.738510f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2A_02,
            }
        }
    },
    // Coastal Remains - Coastal Depot
    {
        .m_MapIndex = 45,
        .m_TrigIndex = 149,
        .m_XYZ = {
            .x = 45.181740f,
            .y = 0.189526f,
            .z = 18.268673f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_MAINSHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2A,
            }
        }
    },
    // Cloudy Domain - Elevator Top
    {
        .m_MapIndex = 20,
        .m_TrigIndex = 115,
        .m_XYZ = {
            .x = -61.589600f,
            .y = 0.310146f,
            .z = -3.942078f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2C_01,
            }
        }
    },
    // Cloudy Domain - Elder's Homestead
    {
        .m_MapIndex = 20,
        .m_TrigIndex = 153,
        .m_XYZ = {
            .x = 216.852676f,
            .y = 17.012980f,
            .z = -5.005016f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2C_02,
            }
        }
    },
    // Cloudy Domain - Tallest Tower
    {
        .m_MapIndex = 20,
        .m_TrigIndex = 165,
        .m_XYZ = {
            .x = 349.804749f,
            .y = 32.733200f,
            .z = -117.013962f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2C_03,
            }
        }
    },
    // Sunken Ruins - Atlantian Entryway
    {
        .m_MapIndex = 19,
        .m_TrigIndex = 368,
        .m_XYZ = {
            .x = -509.105347f,
            .y = -266.824310f,
            .z = 23.030994f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2B_01,
            }
        }
    },
    // Sunken Ruins - The Depths
    {
        .m_MapIndex = 19,
        .m_TrigIndex = 369,
        .m_XYZ = {
            .x = -761.477356f,
            .y = -271.996552f,
            .z = -23.784927f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2B_02,
            }
        }
    },
    // Sunken Ruins - Toxic Rise
    {
        .m_MapIndex = 19,
        .m_TrigIndex = 370,
        .m_XYZ = {
            .x = -664.525452f,
            .y = -311.094360f,
            .z = -98.674156f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R2B_03,
            }
        }
    },
    // Frostbite Village - Eskimole Village
    {
        .m_MapIndex = 31,
        .m_TrigIndex = 84,
        .m_XYZ = {
            .x = 56.908875f,
            .y = -3.894720f,
            .z = 125.925324f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3A_01,
            }
        }
    },
    // Frostbite Village - Icy Camp
    {
        .m_MapIndex = 31,
        .m_TrigIndex = 280,
        .m_XYZ = {
            .x = 175.359985f,
            .y = 4.288493f,
            .z = -290.397675f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3A_02,
            }
        }
    },
    // Frostbite Village - Frosty Depot
    {
        .m_MapIndex = 31,
        .m_TrigIndex = 323,
        .m_XYZ = {
            .x = 3.596106f,
            .y = -2.172524f,
            .z = -76.301186f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_MAINSHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3A,
            }
        }
    },
    // Ice Citadel - Cool Courtyard
    {
        .m_MapIndex = 33,
        .m_TrigIndex = 89,
        .m_XYZ = {
            .x = -784.645569f,
            .y = 51.176964f,
            .z = -346.374115f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3C_04,
            }
        }
    },
    // Ice Citadel - Supercharge Central
    {
        .m_MapIndex = 33,
        .m_TrigIndex = 90,
        .m_XYZ = {
            .x = -570.092590f,
            .y = -10.649817f,
            .z = -176.093781f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3C_01,
            }
        }
    },
    // Ice Citadel - Royal Chamber
    {
        .m_MapIndex = 33,
        .m_TrigIndex = 91,
        .m_XYZ = {
            .x = -487.255676f,
            .y = -6.158705f,
            .z = -314.095551f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3C_03,
            }
        }
    },
    // Ice Citadel - Drawbridge Drop-off
    {
        .m_MapIndex = 33,
        .m_TrigIndex = 92,
        .m_XYZ = {
            .x = -334.914398f,
            .y = 0.127394f,
            .z = -94.521774f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R3C_02,
            }
        }
    },
    // Stormy Beach - Stormy Depot
    {
        .m_MapIndex = 44,
        .m_TrigIndex = 7,
        .m_XYZ = {
            .x = -33.352539f,
            .y = 10.048298f,
            .z = 29.243607f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_MAINSHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4A,
            }
        }
    },
    // Molten Mount - Destroyed Village
    {
        .m_MapIndex = 60,
        .m_TrigIndex = 108,
        .m_XYZ = {
            .x = -26.569090f,
            .y = 50.599999f,
            .z = 655.625122f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4B_01,
            }
        }
    },
    // Molten Mount - Collapsed Bridge
    {
        .m_MapIndex = 60,
        .m_TrigIndex = 113,
        .m_XYZ = {
            .x = -84.515282f,
            .y = 50.599999f,
            .z = 994.028137f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4B_02,
            }
        }
    },
    // Molten Mount - Lumber Storage
    {
        .m_MapIndex = 60,
        .m_TrigIndex = 122,
        .m_XYZ = {
            .x = 214.482681f,
            .y = 50.599999f,
            .z = 1074.337769f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4B_03,
            }
        }
    },
    // Magma Falls Top - Crackling Cave
    {
        .m_MapIndex = 61,
        .m_TrigIndex = 35,
        .m_XYZ = {
            .x = 248.159164f,
            .y = -125.762543f,
            .z = 867.418884f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4C_03,
            }
        }
    },
    // Magma Falls Bottom - Sparx Can Fly
    {
        .m_MapIndex = 63,
        .m_TrigIndex = 21,
        .m_XYZ = {
            .x = -210.990295f,
            .y = -258.878662f,
            .z = -1263.748535f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4C_02,
            }
        }
    },
    // Magma Falls Bottom - Chains of Lava
    {
        .m_MapIndex = 63,
        .m_TrigIndex = 24,
        .m_XYZ = {
            .x = 66.081490f,
            .y = -283.507416f,
            .z = -982.990112f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4C_01,
            }
        }
    },
    // Dark Mine - Mine Mouth
    {
        .m_MapIndex = 30,
        .m_TrigIndex = 134,
        .m_XYZ = {
            .x = -490.521118f,
            .y = -273.301148f,
            .z = -1401.613770f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4D_01,
            }
        }
    },
    // Dark Mine - Hidden Depths
    {
        .m_MapIndex = 30,
        .m_TrigIndex = 144,
        .m_XYZ = {
            .x = -452.249054f,
            .y = -273.172058f,
            .z = -1544.646240f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4D_02,
            }
        }
    },
    // Dark Mine - Miner's Drop
    {
        .m_MapIndex = 30,
        .m_TrigIndex = 146,
        .m_XYZ = {
            .x = -577.123596f,
            .y = -327.917664f,
            .z = -1699.986328f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4D_03,
            }
        }
    },
    // Red's Laboratory - Celestial Show
    {
        .m_MapIndex = 40,
        .m_TrigIndex = 293,
        .m_XYZ = {
            .x = -1186.087769f,
            .y = -307.941559f,
            .z = -1387.263916f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4E_01,
            }
        }
    },
    // Red's Laboratory - Mechanical Mishaps
    {
        .m_MapIndex = 40,
        .m_TrigIndex = 295,
        .m_XYZ = {
            .x = -1486.697022f,
            .y = -308.129211f,
            .z = -1282.904907f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4E_03,
            }
        }
    },
    // Red's Laboratory - Pre-production
    {
        .m_MapIndex = 40,
        .m_TrigIndex = 297,
        .m_XYZ = {
            .x = -992.320435f,
            .y = -307.941589f,
            .z = -1264.443970f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4E_04,
            }
        }
    },
    // Red's Laboratory - Laser Leaps
    {
        .m_MapIndex = 40,
        .m_TrigIndex = 299,
        .m_XYZ = {
            .x = -1052.305298f,
            .y = -290.389160f,
            .z = -1618.039185f
        },
        .m_Type = Type_RestartPoint,
        .u = {
            .RestartPoint = {
                .HasVisited = 1,
                .HashCode = HT_StartPoint_SHOP,
                .NameTextHashCode = HT_Text_ShopPad_R4E_02,
            }
        }
    }
};

MapOrderInfo shops_mapinfos[] = {
    { .m_FileHash = HT_File_Realm1A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm1B,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm1C,    .m_MapHash = 0xFFFFFFFF },

    { .m_FileHash = HT_File_Realm2A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm2B,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm2C,    .m_MapHash = HT_Map_2   },

    { .m_FileHash = HT_File_Realm3A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm3C,    .m_MapHash = 0xFFFFFFFF },

    { .m_FileHash = HT_File_Realm4A,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm4B,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm4C,    .m_MapHash = HT_Map_1   },
    { .m_FileHash = HT_File_Realm4C,    .m_MapHash = HT_Map_3   },
    { .m_FileHash = HT_File_Realm4D,    .m_MapHash = 0xFFFFFFFF },
    { .m_FileHash = HT_File_Realm4E,    .m_MapHash = 0xFFFFFFFF }
};

