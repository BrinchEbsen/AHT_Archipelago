#include <exitemenv.h>
#include <Sound.h>

bool lock_music_to_shop = false;

void XSEItemEnv__StartMusic_ReImplHook(void* self, EXHashCode HashCode, u32 nFlags, s32 FadeOutTime, s32 FadeInTime)
{
    if ((nFlags & 0x10) != 0) {
        XSEItemEnv__StartMusic__LockedFlag = 0;
    }

    if (lock_music_to_shop)
    {
        HashCode = HT_Sound_MFX_Shop;
        FadeOutTime = 0;
        FadeInTime = 0;
    }

    EXItemEnv__StartMusic(self, HashCode, nFlags, FadeOutTime, FadeInTime);

    if ((nFlags & 8) != 0) {
        XSEItemEnv__StartMusic__LockedFlag = 1;
    }

    return;
}
