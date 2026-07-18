#ifndef AP_VERSION_H
#define AP_VERSION_H
#include <types.h>

#ifndef AP_VERSION
#error No AP version defined: Add define for AP_VERSION.
#define AP_VERSION 0
#endif /* AP_VERSION */

extern u32 g_ap_version;

#endif /* AP_VERSION_H */
