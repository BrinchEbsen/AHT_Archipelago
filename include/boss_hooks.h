#ifndef BOSS_HOOKS_H
#define BOSS_HOOKS_H
#include <types.h>
#include <objcollide.h>

extern float gnasty_health_subtract;
extern float ineptune_health_subtract;
extern float red_health_subtract;

#define XSEITEMHANDLER_BOSS__M_NHITSTHISSTAGE(self) OFFSET_VAL(int, self, 0x434)
#define XSEITEMHANDLER_INEPTUNE__M_NUMOFHITS(self) OFFSET_VAL(int, self, 0x578)

extern s32 XSEItemHandler_GnastyGnorc__PlayerAttack(void* self, objCollide* coll);
s32 XSEItemHandler_GnastyGnorc__PlayerAttack_VtableHook(void* self, objCollide* coll);

extern s32 XSEItemHandler_Ineptune__PlayerAttack(void* self, objCollide* coll);
s32 XSEItemHandler_Ineptune__PlayerAttack_VtableHook(void* self, objCollide* coll);

extern void XSEItemHandler_Red__HitByExplosion(void* self);
void XSEItemHandler_Red__HitByExplosion_PreCallHook(void* self);

void ap_setup_boss_damage();

#endif /* BOSS_HOOKS_H */