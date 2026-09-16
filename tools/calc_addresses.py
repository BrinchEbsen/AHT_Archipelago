import subprocess
import os
import sys
from enum import Enum


class StructMember:
    def __init__(self, name: str, offs: int) -> None:
        self.name = name
        self.offs = offs


class Struct:
    def __init__(self, name: str, members: list[StructMember]) -> None:
        self.name = name
        self.members = members

    def get_member(self, name: str) -> StructMember:
        for member in self.members:
            if member.name == name:
                return member
        raise TypeError("Member "+name+" not found in struct.")


class BuildVersion:
    def __init__(
            self, name: str,
            id: str,
            patch_settings_addr: int,
            gs_settings_addr: int,
            notif_addr: int,
            gamestate_addr: int,
            gameloop_addr: int,
            version_addr: int) -> None:
        self.name = name
        self.id = id
        self.patch_settings_addr = patch_settings_addr
        self.gs_settings_addr = gs_settings_addr
        self.notif_addr = notif_addr
        self.gamestate_addr = gamestate_addr
        self.gameloop_addr = gameloop_addr
        self.version_addr = version_addr


class ParseState(Enum):
    FIND_STRUCT = 1
    CHECK_STRUCT_START = 2
    FIND_MEMBERS = 3
    GET_MEMBER_NAME = 4
    GET_MEMBER_OFFS = 5


def find_struct(readelf_lines: list[str], name: str) -> Struct:
    state = ParseState.FIND_STRUCT
    members: list[StructMember] = []
    curr_mem_name = ""

    for line in readelf_lines:
        match state:
            case ParseState.FIND_STRUCT:
                if "DW_TAG_structure_type" in line:
                    state = ParseState.CHECK_STRUCT_START
            case ParseState.CHECK_STRUCT_START:
                if line.endswith(name):
                    state = ParseState.FIND_MEMBERS
                else:
                    state = ParseState.FIND_STRUCT
            case ParseState.FIND_MEMBERS:
                # End of struct
                if "Abbrev Number: 0" in line:
                    break
                if "DW_TAG_member" in line:
                    state = ParseState.GET_MEMBER_NAME
            case ParseState.GET_MEMBER_NAME:
                split = line.split()
                curr_mem_name = split[len(split)-1].strip()
                state = ParseState.GET_MEMBER_OFFS
            case ParseState.GET_MEMBER_OFFS:
                if "DW_AT_data_member_location" in line:
                    split = line.split()
                    offs = split[len(split)-1]
                    members.append(StructMember(curr_mem_name, int(offs)))
                    state = ParseState.FIND_MEMBERS

    if state == ParseState.FIND_STRUCT:
        raise TypeError("Could not find struct "+name)

    return Struct(name, members)


build_versions = [
    BuildVersion("GC_NTSC", "G5SE7D", 0x803D8FA8, 0x80467ce4, 0x8029E1DC, 0x80463b38, 0x8046f2f0, 0x80187620),
    BuildVersion("GC_PAL",  "G5SP7D", 0x803D99F8, 0x804687BC, 0x8029EA4C, 0x80464610, 0x8046fdc8, 0x80187C30)
]


objfiles_path = "../.config/output/object_files/"
objfiles = os.listdir(objfiles_path)

if "MyMod.elf" not in objfiles:
    print("MyMod.elf not found in object files output.")
    sys.exit(1)

try:
    result = subprocess.run(
        ["readelf", "--debug-dump=info", objfiles_path+"MyMod.elf"],
        capture_output=True,
        text=True,
        check=True,
    )
except subprocess.CalledProcessError as e:
    print("Error running readelf: "+e.stderr)
    sys.exit(1)

lines = result.stdout.splitlines()

s_ap_settings   = find_struct(lines, "APSettings")
s_notification  = find_struct(lines, "AP_Notification_Data")
s_gamestate     = find_struct(lines, "SE_GameState")
s_playerstate   = find_struct(lines, "PlayerState")
s_gameloop      = find_struct(lines, "SE_GameLoop")

output: list[str] = []

output.append("class AddressList:\n")
for m in s_ap_settings.members:
    output.append("\tp_"+m.name.upper()+": int\n")
output.append("\n")
for m in s_ap_settings.members:
    output.append("\tg_"+m.name.upper()+": int\n")
output.append("\n")
for m in s_notification.members:
    output.append("\tn_"+m.name.upper()+": int\n")
output.append("\n")
output.append("\tOBJECTIVES: int\n")
output.append("\tDARK_GEM_COUNT: int\n")
output.append("\tLIGHT_GEM_COUNT: int\n")
output.append("\tDRAGON_EGG_COUNT: int\n")
output.append("\tGEMS: int\n")
output.append("\tLOCKPICKS: int\n")
output.append("\tACTIVE_BREATH: int\n")
output.append("\tABILITY_FLAGS: int\n")
output.append("\tIN_GAME: int\n") 
output.append("\tPAUSE: int\n")
output.append("\tFIRE_BOMBS: int\n")
output.append("\tICE_BOMBS: int\n")
output.append("\tWATER_BOMBS: int\n")
output.append("\tELECTRIC_BOMBS: int\n")
output.append("\tHEALTH: int\n")
output.append("\tAP_VERSION_MAJOR: int\n")
output.append("\tAP_VERSION_MINOR: int\n")
output.append("\n\n")

for bv in build_versions:
    output.append("class "+bv.id+"(AddressList):\n")

    # Patch
    for m in s_ap_settings.members:
        output.append("\tp_"+m.name.upper()+" = "+hex(bv.patch_settings_addr + m.offs)+"\n")
    output.append("\n")
    
    # Gamestate
    for m in s_ap_settings.members:
        output.append("\tg_"+m.name.upper()+" = "+hex(bv.gs_settings_addr + m.offs)+"\n")
    output.append("\n")

    # Notification
    for m in s_notification.members:
        output.append("\tn_"+m.name.upper()+" = "+hex(bv.notif_addr + m.offs)+"\n")
    output.append("\n")

    # Globals

    # gGameState.m_PlayerObjectives
    output.append("\tOBJECTIVES = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerObjectives").offs)+
             "\n")
    # gGameState.m_PlayerState.m_TotalDarkGems
    output.append("\tDARK_GEM_COUNT = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_TotalDarkGems").offs)+
             "\n")
    # gGameState.m_PlayerState.m_TotalLightGems
    output.append("\tLIGHT_GEM_COUNT = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_TotalLightGems").offs)+
             "\n")
    # gGameState.m_PlayerState.m_TotalDragonEggs
    output.append("\tDRAGON_EGG_COUNT = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_TotalDragonEggs").offs)+
             "\n")
    # gGameState.m_PlayerState.m_Gems
    output.append("\tGEMS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_Gems").offs)+
             "\n")
    # gGameState.m_PlayerState.m_LockPickers
    output.append("\tLOCKPICKS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_LockPickers").offs)+
             "\n")
    # gGameState.m_PlayerState.m_CurrentBreath
    output.append("\tACTIVE_BREATH = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_CurrentBreath").offs)+
             "\n")
    # gGameState.m_PlayerState.m_AbilityFlags
    output.append("\tABILITY_FLAGS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_AbilityFlags").offs)+
             "\n")
    # gGameLoop.m_State
    output.append("\tIN_GAME = "
        +hex(bv.gameloop_addr+
             s_gameloop.get_member("m_State").offs)+
             "\n")
    # gGameLoop.m_pPanel + 1
    # m_GameIsPaused can't be addressed because it's a bitfield.
    output.append("\tPAUSE = "
        +hex(bv.gameloop_addr+
             s_gameloop.get_member("m_pPanel").offs+4)+
             "\n")
    # gGameState.m_PlayerState.m_FlameBombs
    output.append("\tFIRE_BOMBS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_FlameBombs").offs)+
             "\n")
    # gGameState.m_PlayerState.m_IceBombs
    output.append("\tICE_BOMBS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_IceBombs").offs)+
             "\n")
    # gGameState.m_PlayerState.m_WaterBombs
    output.append("\tWATER_BOMBS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_WaterBombs").offs)+
             "\n")
    # gGameState.m_PlayerState.m_ElectricBombs
    output.append("\tELECTRIC_BOMBS = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_ElectricBombs").offs)+
             "\n")
    # gGameState.m_PlayerState.m_Health
    output.append("\tHEALTH = "
        +hex(bv.gamestate_addr+
             s_gamestate.get_member("m_PlayerState").offs+
             s_playerstate.get_member("m_Health").offs)+
             "\n")

    # AP_VERSION
    output.append("\tAP_VERSION_MAJOR = "+hex(bv.version_addr)+"\n")
    output.append("\tAP_VERSION_MINOR = "+hex(bv.version_addr+2)+"\n")
    output.append("\n\n")

with open("addresses.py", 'w+t') as file:
    file.writelines(output)
