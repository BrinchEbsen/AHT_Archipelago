# Glide button check in HandleEndJump.
.memaddr 0x800a7b9c
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

# Glide button check in HandleFall.
.memaddr 0x800a29ec
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

# Glide button check in TestGlideStart.
.memaddr 0x800a3c98
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

# Jump button check in TestJumpJumpGlide.
.memaddr 0x800a6b7c
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook

# Glide button check in TestGlideEnd.
# This isn't strictly necessary but will ensure glide will end if it somehow starts.
.memaddr 0x800a3ce4
bl glide_XSEItemHandler_Player__ButtonDown_PreCallHook
