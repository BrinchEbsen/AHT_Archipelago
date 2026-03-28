#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <types.h>

//temp
typedef int SE_FileManager;

extern SE_FileManager gSEFileManager;

extern int SE_FileManager__IsGeoLoaded(SE_FileManager* self, EXHashCode* pList);
extern void* SE_FileManager__GetGeoHeader(SE_FileManager* self, EXHashCode Code);

#endif /* FILEMANAGER_H */