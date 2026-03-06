#ifndef AP_NOTIFICATION_H
#define AP_NOTIFICATION_H
#include <types.h>
#include <color.h>

extern RGBA ap_notification_color;
extern u32 ap_notification_timer;

void ap_draw_notification(void* pWnd);
void ap_set_notification(u32 timer, RGBA col, char *text);

#endif /* AP_NOTIFICATION_H */