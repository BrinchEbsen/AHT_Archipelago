#ifndef GAMETEXT_H
#define GAMETEXT_H
#include <types.h>

typedef struct GameText
{
    undefined temp;
} GameText;

extern GameText gGameText;
wchar16* GameText__GetText(GameText* self, EXHashCode Code, EXHashCode *pWho, int *pColour);

#endif /* GAMETEXT_H */