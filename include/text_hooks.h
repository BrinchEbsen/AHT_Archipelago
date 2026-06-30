#ifndef TEXT_HOOKS_H
#define TEXT_HOOKS_H
#include <types.h>

typedef struct 
{
    u32 m_HashCode;
    int m_String;
    int m_UserData;
    u32 m_SoundHashCode;
} EXGeoTextItem;

typedef struct
{
    EXHashCode WhoSaidThat;
    u8 TextFormat;
    u8 OutputTarget;
    u16 Timer;
} xlsUserData;

// extern EXGeoTextItem text_hook_items[];
// extern xlsUserData text_hook_userdata[];
// extern wchar16* text_hook_strings[];

extern EXGeoTextItem unlockshop_buytext_item;
extern xlsUserData unlockshop_buytext_userdata;
extern wchar16* unlockshop_buytext_string;

extern EXGeoTextItem* GameText__FindTextItem(void* self, EXHashCode TextHash);
EXGeoTextItem* GameText__FindTextItem_PreCallHook(void* self, EXHashCode TextHash);

#endif /* TEXT_HOOKS_H */