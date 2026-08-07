#ifndef EX_MEM_H
#define EX_MEM_H
#include <types.h>

typedef u32 EXMemFlags;
extern void* _EXAlloc(size_t size, EXMemFlags memflags);
extern void EXFree(void* pData);

#endif /* EX_MEM_H */
