#ifndef AP_DEATHLINK_H
#define AP_DEATHLINK_H
#include <types.h>
#include <exvector.h>

typedef enum DeathLinkResult
{
    DeathLinkResult_Failed,
    DeathLinkResult_Shielded,
    DeathLinkResult_Died,
    DeathLinkResult_MiniGameFail
} DeathLinkResult;

typedef struct objCollide
{
    int datumflags;
    int hash;
    EXVector vdelta;
    EXVector velocity;
    EXVector position;
    int mask;
    int flags;
    int type;
    int skinflags;
    /* EXItemAnimator* */ void* pAnimator;
} objCollide;

extern void XSEItemHandler_Player__TakeDamage(
    void* self, u32 damage, u32 reactionType, u32 priority, objCollide* coll, char* who, Bool rumble);

extern void XSEItemHandler_BallGadget__TakeDamage(
    void* self, u32 damage, u32 reactionType, u32 priority, objCollide* coll, char* who, Bool rumble);

extern Bool XSEItemHandler_Player__InvulnerableToAttack(void* self, int attack);

#define XSEITEMHANDLER_BALLGADGET_M_PHYSICSFLAGS(self) OFFSET_VAL(u32, self, 0x1440)

extern bool deathlink_ignore_next_death;

void ap_deathlink_update();

DeathLinkResult try_kill_player(bool shielded);

void ap_handle_deathlink_outgoing(u8 reason);

/// @brief Takes away the butterfly jar and returns true if the deathlink should be shielded.
/// @param shielded Whether the deathlink mode is Shielded. If this is false, this always returns false.
bool take_butterfly_jar(bool shielded);

#endif /* AP_DEATHLINK_H */