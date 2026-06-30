#include <text_hooks.h>
#include <hashcodes.h>
#include <ap_settings.h>

EXGeoTextItem unlockshop_buytext_item =
{
    .m_HashCode = HT_Text_ShoppingMsg_Cost,
    .m_String = 0,
    .m_UserData = 0,
    .m_SoundHashCode = 0xFFFFFFFF
};
xlsUserData unlockshop_buytext_userdata =
{
    .WhoSaidThat = 0xFFFFFFFF,
    .TextFormat = 0,
    .OutputTarget = 0,
    .Timer = 0
};
wchar16* unlockshop_buytext_string = u"Unlocked at %i Gems";

EXGeoTextItem* GameText__FindTextItem_PreCallHook(void* self, EXHashCode TextHash)
{
    if (g_gamestate_ap_settings.shop_unlock_mode) {
        if (TextHash == HT_Text_ShoppingMsg_Cost) {
            unlockshop_buytext_item.m_String = (int)unlockshop_buytext_string - (int)&unlockshop_buytext_item.m_String;
            unlockshop_buytext_item.m_UserData = (int)&unlockshop_buytext_userdata - (int)&unlockshop_buytext_item.m_UserData;
            return &unlockshop_buytext_item;
        }
    }

    return GameText__FindTextItem(self, TextHash);
}
