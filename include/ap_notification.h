#ifndef AP_NOTIFICATION_H
#define AP_NOTIFICATION_H
#include <types.h>
#include <color.h>

// The color of the notification text
extern RGBA ap_notification_color;
// The notification timer. If non-zero, it will count down
// and display the notification, until it is zero again.
extern u32 ap_notification_timer;

#define AP_NOTIFICATION_TEXT_BUFFER_SIZE 0x100
// Holds the actual text.
extern wchar16 ap_notification_text_buffer[];

extern bool show_notifications;

void ap_draw_notification(void* pWnd);
void ap_set_notification(u32 timer, RGBA col, wchar16 *text);

#endif /* AP_NOTIFICATION_H */