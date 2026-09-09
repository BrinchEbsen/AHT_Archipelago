#ifndef AP_TRAP_H
#define AP_TRAP_H
#include <types.h>
#include <ap_settings.h>

/// @brief Update function type for traps.
typedef void (*ap_trap_update_func)(u8*);

/// @brief The state of each trap.
/// 0 means non-running.
/// 1 means starting/waiting.
/// 2 and above are different stages of the trap's life cycle.
/// The state is set back to 0 by the update routine when a trap is finished.
extern u8 traps_states[TrapType_NUM];

/// @brief List of update routines for each trap.
extern ap_trap_update_func traps_update_funcs[TrapType_NUM];

/// @brief Update any running traps, and start any that are requested by the client.
void ap_trap_update();



// Trap update routines:

/// @brief Play a random moneybags line and lock the music to the shop music.
void ap_trap_moneybags_spam_call_update(u8* state);

/// @brief Reverse the x-axis of the analog sticks.
void ap_trap_reverse_controls_update(u8* state);

#endif /* AP_TRAP_H */
