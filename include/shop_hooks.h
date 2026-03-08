#ifndef SHOP_HOOKS_H
#define SHOP_HOOKS_H
#include <types.h>
#include <spreadsheet.h>

void* SE_SpreadSheet__OpenSpreadSheet_FileHash_PreCallHook(
    SE_SpreadSheet* self, EXHashCode FileHash, EXHashCode SpreadSheetHash);

#endif /* SHOP_HOOKS_H */