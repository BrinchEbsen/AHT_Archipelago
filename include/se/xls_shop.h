#ifndef XLS_SHOP_H
#define XLS_SHOP_H
#include <types.h>

typedef struct xlsShoppingItem
{
    /* 0x00 */ EXHashCode Entity;
    /* 0x04 */ EXHashCode File;
    /* 0x08 */ EXHashCode ItemText;
    /* 0x0c */ EXHashCode DescText;
    /* 0x10 */ short unsigned int cost[2];
    /* 0x14 */ s16 Count;
    /* 0x16 */ s16 Num;
    /* 0x18 */ u32 AvailableFlags;
    /* 0x1c */ u32 BroughtFlags;
} xlsShoppingItem; // Size: 0x20

#endif /* XLS_SHOP_H */