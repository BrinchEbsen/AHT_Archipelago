#ifndef AP_NOTIFICATION_H
#define AP_NOTIFICATION_H
#include <types.h>
#include <color.h>

#define AP_NOTIFICATION_TEXT_BUFFER_SIZE 0x100

typedef struct AP_Notification_Data {
    // The color of the notification text
    RGBA color;
    // The notification timer. If non-zero, it will count down
    // and display the notification, until it is zero again.
    u32 timer;
    // Holds the actual text.
    wchar16 text_buffer[AP_NOTIFICATION_TEXT_BUFFER_SIZE];
} AP_Notification_Data; // Size: 0x208

// The data for the notification.
// Should be written to by the client.
extern AP_Notification_Data notif_data;

// Whether to show notifications.
extern bool show_notifications;

// Display the current notification and decrement the timer.
void ap_draw_notification(void* pWnd);

// (Debug) Set a notification.
void ap_set_notification(u32 timer, RGBA col, wchar16 *text);

#endif /* AP_NOTIFICATION_H */