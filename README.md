# Spyro: A Hero's Tail - Archipelago Interface Mod

Code injection mod for Spyro: A Hero's Tail that provides an interface for Maya/Xua's [Archipelago client](https://github.com/XuaTheGrate/spyro-aht-ap) for the game, as well as implementing several features suitable for Archipelago.

Read more about Archipelago here: https://archipelago.gg/

Created using Composer's [code injection utility](https://github.com/C0mposer/C-Game-Modding-Utility).

## Compatibility
This mod is currently limited specifically to the NTSC GameCube version (G5SE7D). There are plans to port it to the NTSC PS2 version in the future.

| Platform | NTSC | PAL   |
| -------- | ---- | ----- |
| GameCube | ✅    | ❌     |
| PS2      | ❌    | ❌     |
| Xbox     | ❌    | ❌     |

## Installation/Usage
The mod is installed through an Action Replay code in Dolphin. Open the properties menu for Spyro: A Hero's Tail (G5SE7D) in the game list, go to AR Codes, then add a new code with the contents of `AR_Code.txt`, which you can find in the [lastest release](https://github.com/BrinchEbsen/AHT_Archipelago/releases). Make sure the code is enabled, and that "enable cheats" is enabled in Dolphin.

See further instructions on the [client's github](https://github.com/XuaTheGrate/spyro-aht-ap).

## Building
1. Download the [code injection utility](https://github.com/C0mposer/C-Game-Modding-Utility) by Composer.
2. Clone this repository into the tool's `projects` folder.
3. In the GUI or by editing the .modproj folder itself, edit the paths for the extracted game folder to your own.
4. Build the project using the GUI, or alternatively the CLI:<br>
`mod_utility build AHT_Archipelago --build=GAMECUBE_NTSC`<br>
The resulting modded ISO should be in the project's `build` folder.

## Purpose of the mod
Spyro AHT is a pretty hard game to track the collectables of, so the initial motivation for the mod was to make the game document the collectables in an easily readable format for the client. The mod has since been expanded to include disabling/enabling of basic abilities, randomization of prices and gate requirements, skipping cutscenes, adding custom menu elements, adding custom items to the shop, and more.

The mod uses an empty region in the savefile to store Archipelago-related settings and location data. The game is patched to leave abilities and collectable counts alone, so the client can change them on its own. It also exposes a bunch of settings the client will modify to enable or disable certain features, such as cutscene skipping or immediate access to every realm. Space in the savefile is also allocated for custom shop items, complete with custom text and randomized prices.

A big thanks should go to Maya/Xua for starting the project, developing the client, and getting me interested in working alongside her. This project has been taken far further than I ever imagined.
