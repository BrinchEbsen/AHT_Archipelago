#ifndef EX_ITEM_ENV_H
#define EX_ITEM_ENV_H
#include <types.h>

extern void* EXItemEnv__m_pTheItemEnv;

/// @brief Lock the music to only be the shop music.
extern bool lock_music_to_shop;

extern void EXItemEnv__StartMusic(void* self, EXHashCode HashCode, u32 nGeoSoundFlags, s32 FadeOutTime, s32 FadeInTime);
void XSEItemEnv__StartMusic_ReImplHook(void* self, EXHashCode HashCode, u32 nFlags, s32 FadeOutTime, s32 FadeInTime);
extern u32 XSEItemEnv__StartMusic__LockedFlag;

#endif /* EX_ITEM_ENV_H */