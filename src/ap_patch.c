#include <ap_patch.h>
#include <playerstate.h>

APSettings g_patch_ap_settings = {
    .location_bitfield = {0},
    .starting_breath = fire,
    .starting_abilities = ABILITY_AP_FIREBREATH | ABILITY_AP_CHARGE | ABILITY_AP_GLIDE | ABILITY_AP_SWIM,
    .free_realm_travel_enable = false,
    .skip_realm_intro_cutscenes = false,
    .skip_cutscene_button = true,
    .init = 0
};