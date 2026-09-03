#ifndef AP_BUILD_CONFIG_H
#define AP_BUILD_CONFIG_H

/*
 * General build configuration for the mod.
 * Settings can be overridden with compiler flags.
 * Debug options can be forced off with "-D AP_DEBUG_ENABLE=0".
 */

// ---------------------------------------------------- OPTIONS (GENERAL) ----------------------------------
#define _build_config_AP_VERSION_NUMBER_MAJOR           15      // Version number (major).
#define _build_config_AP_VERSION_NUMBER_MINOR           0       // Version number (minor).
#define _build_config_AP_DEBUG_ENABLE                   0       // Enable debug options (DISABLE FOR RELEASE!).
// ---------------------------------------------------- OPTIONS (DEBUG) ------------------------------------
#define _build_config_AP_DEBUG_QUICK_START              1       // Patch is automatically written to and game will start with some abilities unlocked.
#define _build_config_AP_DEBUG_ADD_REMOVE_SHOP_ITEMS    0       // B+right to append dummy shop item to list, B+left to remove shop item.
#define _build_config_AP_DEBUG_NOTIFICATION             0       // Dpad down to display test notification.
#define _build_config_AP_DEBUG_DEATHLINK                0       // B+dpad to trigger deathlink events, info printed to the screen.
// ---------------------------------------------------------------------------------------------------------





#ifndef AP_VERSION_NUMBER_MAJOR
#define AP_VERSION_NUMBER_MAJOR _build_config_AP_VERSION_NUMBER_MAJOR
#endif /* AP_VERSION_NUMBER_MAJOR */
#ifndef AP_VERSION_NUMBER_MINOR
#define AP_VERSION_NUMBER_MINOR _build_config_AP_VERSION_NUMBER_MINOR
#endif /* AP_VERSION_NUMBER_MINOR */
#ifndef AP_DEBUG_ENABLE
#define AP_DEBUG_ENABLE _build_config_AP_DEBUG_ENABLE
#endif /* AP_DEBUG_ENABLE */
#if AP_DEBUG_ENABLE != 0
#ifndef AP_DEBUG_QUICK_START
#define AP_DEBUG_QUICK_START _build_config_AP_DEBUG_QUICK_START
#endif /* AP_DEBUG_QUICK_START */
#ifndef AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
#define AP_DEBUG_ADD_REMOVE_SHOP_ITEMS _build_config_AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
#endif /* AP_DEBUG_ADD_REMOVE_SHOP_ITEMS */
#ifndef AP_DEBUG_NOTIFICATION
#define AP_DEBUG_NOTIFICATION _build_config_AP_DEBUG_NOTIFICATION
#endif /* AP_DEBUG_NOTIFICATION */
#ifndef AP_DEBUG_DEATHLINK
#define AP_DEBUG_DEATHLINK _build_config_AP_DEBUG_DEATHLINK
#endif /* AP_DEBUG_DEATHLINK */
#else /* AP_DEBUG_ENABLE != 0 */
#ifndef AP_DEBUG_QUICK_START
#define AP_DEBUG_QUICK_START 0
#endif /* AP_DEBUG_QUICK_START */
#ifndef AP_DEBUG_ADD_REMOVE_SHOP_ITEMS
#define AP_DEBUG_ADD_REMOVE_SHOP_ITEMS 0
#endif /* AP_DEBUG_ADD_REMOVE_SHOP_ITEMS */
#ifndef AP_DEBUG_NOTIFICATION
#define AP_DEBUG_NOTIFICATION 0
#endif /* AP_DEBUG_NOTIFICATION */
#ifndef AP_DEBUG_DEATHLINK
#define AP_DEBUG_DEATHLINK 0
#endif /* AP_DEBUG_DEATHLINK */
#endif /* AP_DEBUG_ENABLE != 0 */

#endif /* AP_BUILD_CONFIG_H */
