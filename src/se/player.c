#include <player.h>
#include <pad.h>

bool g_scanmode_enable = false;

bool XSEItemHandler_Player__TestScanMode_ReImplHook(void* self, int current_mode)
{
    if (!g_scanmode_enable) {
        return false;
    }

    return g_pad_button_edge_down(PAD_BUTTON_Z);
}
