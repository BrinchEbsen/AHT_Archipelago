#ifndef AP_TRAP_H
#define AP_TRAP_H
#include <types.h>
#include <ap_settings.h>

typedef void (*ap_trap_update_func)(u8*);

extern u8 traps_states[TrapType_NUM];
extern ap_trap_update_func traps_update_funcs[TrapType_NUM];

void ap_trap_update();

void ap_trap_moneybags_spam_call_update(u8* state);
void ap_trap_reverse_controls_update(u8* state);

#endif /* AP_TRAP_H */
