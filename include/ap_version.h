#ifndef AP_VERSION_H
#define AP_VERSION_H
#include <types.h>

#ifndef AP_VERSION
#error No AP version defined: Add define for AP_VERSION.
#define AP_VERSION 0
#endif /* AP_VERSION */

/// @brief The current version of this mod. Defined in the compiler flags as: `-D AP_VERSION [version number]`.
extern u32 g_ap_version;

#endif /* AP_VERSION_H */
