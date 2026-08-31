#include <ap_notification.h>
#include <color.h>
#include <paneldraw.h>
#include <igstdlib.h>
#include <wnd.h>
#include <player.h>
#include <util.h>

bool show_notifications = true;

void ap_draw_notification(void *pWnd)
{
    if (notif_data.timer == 0) {
        return;
    }

    if (notif_data.text_buffer[0] == 0) {
        return;
    }

    u16 y = 120;
    if (gpPlayer != NULL) {
        if (XSEItemHandler_Player__M_PLAYERTYPE(gpPlayer) == Player_Sparx) {
            y = 160;
        }
    }

    notif_data.timer--;
    
    if (show_notifications) {
        textprintw(pWnd, 2, y, 1.0f, TopLeft, notif_data.color, true, notif_data.text_buffer);
    }
}

void ap_set_notification(u32 timer, RGBA col, wchar16 *text)
{
    notif_data.timer = timer;
    notif_data.color.rgba = col.rgba;

    int len = wstrlen(text);
    memcpy(notif_data.text_buffer, text, len*2 + 1);
}
