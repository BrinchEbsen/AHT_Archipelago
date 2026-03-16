#include <ap_notification.h>
#include <color.h>
#include <paneldraw.h>
#include <igstdlib.h>
#include <wnd.h>

RGBA ap_notification_color = {
    .r = 0x80,
    .g = 0x80,
    .b = 0x80,
    .a = 0x80
};

u32 ap_notification_timer = 0;

char ap_notification_text_buffer[AP_NOTIFICATION_TEXT_BUFFER_SIZE];

void ap_draw_notification(void *pWnd)
{
    if (ap_notification_timer == 0) {
        return;
    }

    if (ap_notification_text_buffer[0] == 0) {
        return;
    }

    TEXT_PRINT_ALIGN_COLOR(pWnd, 2, 120, TopLeft, ap_notification_color, ap_notification_text_buffer);
    
    ap_notification_timer--;
}

void ap_set_notification(u32 timer, RGBA col, char *text)
{
    ap_notification_timer = timer;
    ap_notification_color.rgba = col.rgba;
    strcpy(ap_notification_text_buffer, text);
}
