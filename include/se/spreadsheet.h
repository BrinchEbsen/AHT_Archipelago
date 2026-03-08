#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <types.h>

typedef struct SE_SpreadSheet
{
    void* m_pSpreadSheet;
    EXHashCode m_File;
    void* __vtable;
} SE_SpreadSheet;

#endif /* SPREADSHEET_H */