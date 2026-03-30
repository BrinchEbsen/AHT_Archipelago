#ifndef OBJCOLLIDE_H
#define OBJCOLLIDE_H
#include <exvector.h>

typedef struct objCollide
{
    int datumflags;
    int hash;
    EXVector vdelta;
    EXVector velocity;
    EXVector position;
    int mask;
    int flags;
    int type;
    int skinflags;
    /* EXItemAnimator* */ void* pAnimator;
} objCollide;

#endif /* OBJCOLLIDE_H */