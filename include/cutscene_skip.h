#ifndef CUTSCENE_SKIP_H
#define CUTSCENE_SKIP_H
#include <types.h>
#include <map.h>

#define GET_MAP_LOADING (gMapList.m_List[0].m_pMap)
#define GET_MAP_TITLES  (gMapList.m_List[56].m_pMap)

#define XITEMHANDLER_CUTSCENE_M_FILE_HASH(self) OFFSET_VAL(EXHashCode, self, 0x428)
#define XITEMHANDLER_CUTSCENE_M_SCENE_HASH(self) OFFSET_VAL(EXHashCode, self, 0x42c)
#define XITEMHANDLER_CUTSCENE_M_PSCRIPT(self) OFFSET_VAL(void*, self, 0x434)

typedef struct FileSceneHash
{
    EXHashCode file_hash;
    EXHashCode scene_hash;
} FileSceneHash;

extern FileSceneHash cutscenes_to_ignore[];

extern int XItemHandler_Cutscene__Update(void* self);
extern void EXItemAnimator_Script__SetScriptStatus(void* self, u32 Status);

int XItemHandler_Cutscene__Update_VtableHook(void* self);

void skip_cutscene(void* p_cutscene_camera);

#endif /* CUTSCENE_SKIP_H */