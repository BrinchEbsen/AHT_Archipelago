#ifndef SAVEDGAME_H
#define SAVEDGAME_H
#include <types.h>
#include <gamestate.h>

typedef struct SavedGame
{
    u32 m_UsageFlag;
    u8 m_UsedFlag;
    u8 m_DisplayedSaveMessage;
    u8 m_SpareFlag2;
    u8 m_SpareFlag3;
    SE_GameState m_GameState;
    u8 _pad0[4];
} SavedGame;

_Static_assert(sizeof(SavedGame) == 0xb260);

#endif /* SAVEDGAME_H */