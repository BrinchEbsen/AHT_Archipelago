#ifndef EX_RAND_H
#define EX_RAND_H
#include <types.h>

typedef struct EXRandClass
{
    u32 m_RandShift;
} EXRandClass;

extern EXRandClass g_EXRandClass;

u32 EXRandClass__Rand32(EXRandClass* self);
float EXRandClass__Randf(EXRandClass* self);

#define RAND32  EXRandClass__Rand32(&g_EXRandClass)
#define RANDF   EXRandClass__Randf(&g_EXRandClass)

#endif /* EX_RAND_H */
