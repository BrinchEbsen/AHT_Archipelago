#include <boss_hooks.h>
#include <ap_settings.h>

s32 XSEItemHandler_GnastyGnorc__PlayerAttack_VtableHook(void* self, objCollide* coll)
{
    if (g_gamestate_ap_settings.boss_easy_mode[0]) {
        XSEITEMHANDLER_BOSS__M_NHITSTHISSTAGE(self) = 2;
    }

    return XSEItemHandler_GnastyGnorc__PlayerAttack(self, coll);
}

s32 XSEItemHandler_Ineptune__PlayerAttack_VtableHook(void* self, objCollide* coll)
{
    if (g_gamestate_ap_settings.boss_easy_mode[1]) {
        XSEITEMHANDLER_INEPTUNE__M_NUMOFHITS(self) = 2;
    }

    return XSEItemHandler_Ineptune__PlayerAttack(self, coll);
}

void XSEItemHandler_Red__HitByExplosion_PreCallHook(void* self)
{
    if (g_gamestate_ap_settings.boss_easy_mode[2]) {
        XSEITEMHANDLER_BOSS__M_NHITSTHISSTAGE(self) = 2;
    }

    XSEItemHandler_Red__HitByExplosion(self);
}

void ap_setup_boss_damage() {
    if (g_gamestate_ap_settings.boss_easy_mode[0]) {
        gnasty_health_subtract = 1.0f / 3.0f;
    } else {
        gnasty_health_subtract = 1.0f / 9.0f;
    }

    if (g_gamestate_ap_settings.boss_easy_mode[1]) {
        ineptune_health_subtract = 1.0f / 3.0f;
    } else {
        ineptune_health_subtract = 1.0f / 9.0f;
    }
    
    if (g_gamestate_ap_settings.boss_easy_mode[2]) {
        red_health_subtract = 1.0f / 3.0f;
    } else {
        red_health_subtract = 1.0f / 9.0f;
    }

    // Assembly patches for Mecha Red

    if (g_gamestate_ap_settings.boss_easy_mode[3]) {
        *((u32*)0x8003b314) = 0x3ba00024; // li r29, 36
        *((u32*)0x8003b358) = 0x3ba00009; // li r29, 9
        *((u32*)0x8003b384) = 0x3ba00006; // li r29, 6
    } else {
        *((u32*)0x8003b314) = 0x3ba0000c; // li r29, 12
        *((u32*)0x8003b358) = 0x3ba00003; // li r29, 3
        *((u32*)0x8003b384) = 0x3ba00002; // li r29, 2
    }
}