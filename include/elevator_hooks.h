#ifndef ELEVATOR_HOOKS_H
#define ELEVATOR_HOOKS_H
#include <types.h>
#include <hashcodes.h>

#define ELEVATOR_2C_2A_MAPINDEX             45
#define ELEVATOR_2C_2A_STARTPOINT           HT_StartPoint_Restart2

#define ELEVATOR_2A_2C_MAPINDEX             20
#define ELEVATOR_2A_2C_STARTPOINT           HT_StartPoint_START

#define ELEVATOR_SUNKENRUINS_TRIGGERINDEX   4
#define ELEVATOR_SUNKENRUINS_MAPINDEX       46

#define ELEVATOR_2B_2A_MAPINDEX             45
#define ELEVATOR_2B_2A_STARTPOINT           HT_StartPoint_Restart8

#define ELEVATOR_2A_2B_MAPINDEX             19
#define ELEVATOR_2A_2B_STARTPOINT           HT_StartPoint_Restart1

#define ELEVATOR_MAGMAFALLS_TRIGGERINDEX    4
#define ELEVATOR_MAGMAFALLS_MAPINDEX        57

#define ELEVATOR_4B_4C_MAPINDEX             61
#define ELEVATOR_4B_4C_STARTPOINT           HT_StartPoint_Restart1

#define ELEVATOR_4C_4B_MAPINDEX             60
#define ELEVATOR_4C_4B_STARTPOINT           HT_StartPoint_Restart9

// Existing functions:

extern void SXI_Path__MoveAlongPath(void* self, float DeltaDist, Bool UseSpline);
extern void FlippingPlatform__HandleFlip(void* self);

// Teleport to a map and startpoint
void teleport_to_elevator_endpoint(int map_index, EXHashCode startpoint);

// The Cloudy Domain elevator has its own special class, so a simpler hook is used

// Elevator from Coastal Remains to Cloudy Domain
void SXI_Path__MoveAlongPath_PreCallHook_2Ato2C(void* self, float DeltaDist, Bool UseSpline);
// Elevator from Cloudy Domain to Coastal Remains
void SXI_Path__MoveAlongPath_PreCallHook_2Cto2A(void* self, float DeltaDist, Bool UseSpline);

// Check if a FlippingPlatform is an elevator that should teleport
void test_elevator_teleport(void* elevator);

// Every other elevator
void FlippingPlatform__HandleFlip_PreCallHook(void* self);

#endif /* ELEVATOR_HOOKS_H */