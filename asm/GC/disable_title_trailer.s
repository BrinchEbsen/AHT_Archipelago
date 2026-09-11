# Disables the trailer movie playing on the title screen
# when left idle for 30 seconds.
# 
# Normally this compares the idle pad timer to 30 seconds.
# This compares 30 seconds to 30 seconds, so the 'ble-'
# branch afterwards is always taken.
fcmpu cr0, 0, 0
