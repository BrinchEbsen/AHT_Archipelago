.memaddr 0x800a7b9c
# Glide button check in HandleEndJump.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a29ec
# Glide button check in HandleFall.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a3c98
# Glide button check in TestGlideStart.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a6b7c
# Jump button check in TestJumpJumpGlide.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a3ce4
# Glide button check in TestGlideEnd.
# This isn't strictly necessary but will ensure glide will end if it somehow starts.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook
