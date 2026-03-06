#ifndef AP_HANDLER_H
#define AP_HANDLER_H
#include <types.h>
#include <gameflow.h>

// runs every frame
void ap_update();

void ap_draw();

void SE_GameState__Init_PostHook();

void ap_init_gamestate();

void ap_set_grabbable(u16 map_index, u16 trigger_index);

void ap_set_objective(EXHashCode objective);

void ap_set_location(int index);

int ap_binary_search_grabbable(u16 map_index, u16 trigger_index);

void print_trigger_array_code();

s32 SEGameFlow__v_StateRunning__VTHOOK(SEGameFlow* self);

#endif /* AP_HANDLER_H */