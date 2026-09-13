#ifndef TRIGGER_HOOKS_H
#define TRIGGER_HOOKS_H
#include <types.h>
#include <trigger.h>

#if defined(BUILD_NTSC)
#define CORRECT_DARK_MINE_LOADING_TRIGGER
#endif

extern void* EXItemAnimator_Map__GetGeoMap(void* self);
extern void SE_TriggerList__ConstructAll(SE_TriggerList* self);

void SE_TriggerList__ConstructAll_PreCallHook(SE_TriggerList* self);

#if defined(CORRECT_DARK_MINE_LOADING_TRIGGER)
// Take the EXGeoMap for Dark Mine and give that one broken
// loading trigger a new rotation value to match PAL.
void correct_dark_mine_loading_trigger(void* p_geo_map);
#endif

#endif /* TRIGGER_HOOKS_H */
