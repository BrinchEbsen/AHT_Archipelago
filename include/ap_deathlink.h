#ifndef AP_DEATHLINK_H
#define AP_DEATHLINK_H
#include <types.h>
#include <objcollide.h>
#include <ap_settings.h>

// What happened when the deathlink was executed on the player.
typedef enum DeathLinkResult
{
    // The player could not be killed.
    DeathLinkResult_Failed,
    // The deathlink was executed, and was shielded by a butterfly jar.
    DeathLinkResult_Shielded,
    // The player died.
    DeathLinkResult_Died,
    // The player failed a turret minigame.
    DeathLinkResult_MiniGameFail
} DeathLinkResult;

extern void XSEItemHandler_Player__TakeDamage(
    void* self, u32 damage, u32 reactionType, u32 priority, objCollide* coll, char* who, Bool rumble);

extern void XSEItemHandler_BallGadget__TakeDamage(
    void* self, u32 damage, u32 reactionType, u32 priority, objCollide* coll, char* who, Bool rumble);

extern Bool XSEItemHandler_Player__InvulnerableToAttack(void* self, int attack);

#define XSEITEMHANDLER_BALLGADGET_M_PHYSICSFLAGS(self) OFFSET_VAL(u32, self, 0x1440)

// The next death should not incur a deathlink.
extern bool deathlink_ignore_next_death;

// Check if the player should be killed from a deathlink.
void ap_deathlink_update();

/// @brief Attempt to kill the player from a deathlink.
/// @param shielded Whether this deathlink should be shielded with the butterfly jar.
/// @return The result of trying to kill the player.
DeathLinkResult try_kill_player(bool shielded);

// Output a deathlink signal, unless the next death is ignored.
void ap_handle_deathlink_outgoing(DeathLinkReason reason);

/// @brief Takes away the butterfly jar and returns true if the deathlink should be shielded.
/// @param shielded Whether the deathlink mode is Shielded. If this is false, this always returns false.
bool take_butterfly_jar(bool shielded);

#endif /* AP_DEATHLINK_H */