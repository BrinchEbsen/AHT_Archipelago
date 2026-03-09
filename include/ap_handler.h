#ifndef AP_HANDLER_H
#define AP_HANDLER_H
#include <types.h>
#include <gameflow.h>
#include <gamestate.h>

// runs every frame
void ap_update();

void dbg_add_shop_item();

void dbg_remove_shop_item();

void ap_draw(void* pWnd);

void ap_init_gamestate();

bool TeleportPad_PlayerObjectives__GetObjective_PreCallHook(
    PlayerObjectives* self, EXHashCode hashcode, s32* result);

void ap_set_grabbable(u16 map_index, u16 trigger_index);

void ap_set_objective(EXHashCode objective);

void ap_set_location(int index);

int ap_binary_search_grabbable(u16 map_index, u16 trigger_index);

s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow* self);

#endif /* AP_HANDLER_H */