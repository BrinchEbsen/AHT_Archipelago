#ifndef SYSCALLS_H
#define SYSCALLS_H

// PS2 BIOS Syscall - _print
// Uses syscall 0x75
int _print(const char* format, ...);

#endif // SYSCALLS_H
