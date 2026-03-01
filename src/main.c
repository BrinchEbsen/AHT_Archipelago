#include <types.h>
#include <symbols.h>
#include <ap_handler.h>
#include <syscalls.h>

#if GC_NTSC
void ModMain(void) {
    ap_update();
}
#elif PS2_NTSC
int ModMain(void) {
    int ret = _sceSifSendCmd(); // MUST keep as first line. This is the function that was replaced by the hook.
    ap_update();
    return ret; // MUST keep as last line. This is the return value from the replaced function.
}
#else
#error Cannot define ModMain: No compatible build version
#endif