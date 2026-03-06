#include <ap_notification.h>
#include <color.h>
#include <paneldraw.h>
#include <igstdlib.h>

RGBA ap_notification_color = {
    .r = 0xFF,
    .g = 0xFF,
    .b = 0xFF,
    .a = 0xFF
};

u32 ap_notification_timer = 0;

char text_buffer[0x100];

void ap_draw_notification(void *pWnd)
{
    if (ap_notification_timer == 0) {
        return;
    }

    if (text_buffer[0] == 0) {
        return;
    }

    TEXT_PRINT_ALIGN_COLOR(pWnd, 0, 0, CentreLeft, ap_notification_color, text_buffer);
    
    ap_notification_timer--;
}

void ap_set_notification(u32 timer, RGBA col, char *text)
{
    ap_notification_timer = timer;
    ap_notification_color.rgba = col.rgba;
    strcpy(text_buffer, text);
}
