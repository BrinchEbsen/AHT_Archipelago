#ifndef SYSTEM_H
#define SYSTEM_H

#if GC_NTSC

#include <os.h>
#define PRINTF(fmt, ...) OSReport(fmt, ##__VA_ARGS__)

#elif PS2_NTSC

#include <syscalls.h>
#define PRINTF(fmt, ...) _print(fmt, ##__VA_ARGS__)

#else // FALLBACK

#warning Build version could not be identified
#define PRINTF(fmt, ...)

#endif

#endif /* SYSTEM_H */