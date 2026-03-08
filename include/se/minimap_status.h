#ifndef MINIMAP_STATUS_H
#define MINIMAP_STATUS_H
#include <types.h>
#include <bitheap.h>

typedef enum BitNames
{
    Visible,
    Selectable,
    NumBits
} BitNames;

typedef struct MapOrderInfo
{
    EXHashCode m_FileHash;
    EXHashCode m_MapHash;
} MapOrderInfo;

typedef struct MiniMapStatus
{
    SE_BitHeap* m_pBitHeap;
    s32 m_BitHeapAddress;
    u32 m_BitStride;
    u32 m_NumEntries;
    MapOrderInfo m_Current;
    s32 m_CurrentShopRestart;
} MiniMapStatus;

extern MiniMapStatus gMiniMapStatus;

extern void MiniMapStatus__SetBitName(MiniMapStatus* self, MapOrderInfo *Code, BitNames Bit);

#endif /* MINIMAP_STATUS_H */