#ifndef XLS_SHOP_H
#define XLS_SHOP_H
#include <types.h>

typedef struct xlsShoppingItem
{
    EXHashCode Entity;
    EXHashCode File;
    EXHashCode ItemText;
    EXHashCode DescText;
    short unsigned int cost[2];
    s16 Count;
    s16 Num;
    u32 AvailableFlags;
    u32 BroughtFlags;
} xlsShoppingItem;

#endif /* XLS_SHOP_H */