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

## Building (for developers)

1. Download the [code injection utility](https://github.com/C0mposer/C-Game-Modding-Utility/releases) by Composer.

2. Clone this repository into the tool's `projects` folder.
3. In the GUI or by editing the .modproj folder itself, edit the paths for the extracted game folder to your own.
4. Build the project using the GUI, or alternatively the CLI:<br>
`mod_utility build AHT_Archipelago --build=GAMECUBE_NTSC`<br>
The resulting modded ISO should be in the project's `build` folder.
