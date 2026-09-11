.memaddr 0x800a7c6c
# Glide button check in HandleEndJump.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a2a90
# Glide button check in HandleFall.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a3d3c
# Glide button check in TestGlideStart.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a6c4c
# Jump button check in TestJumpJumpGlide.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

.memaddr 0x800a3d88
# Glide button check in TestGlideEnd.
# This isn't strictly necessary but will ensure glide will end if it somehow starts.
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook
