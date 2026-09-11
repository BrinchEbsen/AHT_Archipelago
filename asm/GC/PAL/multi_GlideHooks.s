.memaddr 0x
# Glide button check in HandleEndJump.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Glide button check in HandleFall.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Glide button check in TestGlideStart.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Jump button check in TestJumpJumpGlide.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x
# Glide button check in TestGlideEnd.
# This isn't strictly necessary but will ensure glide will end if it somehow starts.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook
