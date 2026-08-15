# Spyro: A Hero's Tail - Archipelago Interface Mod

Code injection mod for Spyro: A Hero's Tail that provides an interface for the [Archipelago client](https://github.com/seanstan95/PhoenixAP/tree/AHTEdits) for the game by Maya/Xua and PhoenixAki, as well as implementing several features suitable for Archipelago.

Read more about Archipelago here: <https://archipelago.gg/>

Read the setup guide for the client here: <https://github.com/seanstan95/PhoenixAP/wiki/Spyro:-AHT-0.5-%E2%80%90-Introduction>

Created using Composer's [code injection utility](https://github.com/C0mposer/C-Game-Modding-Utility).

## Compatibility

This mod is currently limited specifically to the NTSC GameCube version (G5SE7D).

| Platform | NTSC | PAL |
| -------- | ---- | --- |
| GameCube | ✅   | ❌  |
| PS2      | ❌   | ❌  |
| Xbox     | ❌   | ❌  |

## Installation/Usage

The mod is installed through an Action Replay (AR) code in Dolphin. The latest code can be found in a text file in the client's latest release: <https://github.com/seanstan95/PhoenixAP/releases/latest>

Open the properties menu for Spyro: A Hero's Tail (G5SE7D) in the game list, go to AR Codes, then add a new code with the contents of the text file. Make sure the code is enabled, and that "enable cheats" is enabled in Dolphin.

## For Developers

### Wiki

There's a [wiki](https://github.com/BrinchEbsen/AHT_Archipelago/wiki) with a bunch of technical information about the mod, to serve as reference for client devs.

### Building AR Code

#### Setup

Download the [code injection utility](https://github.com/C0mposer/C-Game-Modding-Utility/releases) by Composer.

Clone this repository into the tool's `projects` folder.

#### Building (GUI)

Open the project in the GUI by clicking "Load Existing Project" and choosing the .modproj in the cloned repository.

Go to the "Build Project" tab and click "Compile".

Once compilation is finished, click "Generate Action Replay Code" to generate the code for the mod.

#### Building (CLI)

Run the following command on `mod_utility.exe` to output a text file with the code:

`mod_utility export-cheat AHT_Archipelago action_replay --build=GC_NTSC --output=AR_Code.txt`

Note that the resulting `AR_Code.txt` will have two extra lines at the top, which aren't part of the code that goes in Dolphin.
