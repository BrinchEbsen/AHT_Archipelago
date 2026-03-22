#include <ap_deathlink.h>
#include <player.h>
#include <ap_settings.h>
#include <gamestate.h>
#include <gameloop.h>
#include <hashcodes.h>

bool deathlink_ignore_next_death = false;

void ap_deathlink_update()
{
    if (g_gamestate_ap_settings.deathlink_ingoing != 0) {
        bool shielded = g_gamestate_ap_settings.deathlink_ingoing == AP_DEATHLINK_MODE_SHIELDED;
        
        DeathLinkResult res = try_kill_player(shielded);

        if (res != DeathLinkResult_Failed) {
            g_gamestate_ap_settings.deathlink_ingoing = 0;
        }

        if (res == DeathLinkResult_Died) {
            deathlink_ignore_next_death = true;
        }
    }
}

DeathLinkResult try_kill_player(bool shielded)
{
    // if paused
    if (gGameLoop.m_GameIsPaused) {
        return DeathLinkResult_Failed;
    }

    // if player doesn't exist
    if (gpPlayer == NULL) {
        return DeathLinkResult_Failed;
    }

    // if controls locked
    if (XSEItemHandler_Player__ControlsLocked(gpPlayer)) {
        return DeathLinkResult_Failed;
    }

    // if in cutscene mode
    PlayerModes currmode = XSEItemHandler_Player__M_PLAYERMODE(gpPlayer);
    if ((currmode == listen) || (currmode == listen_water)) {
        return DeathLinkResult_Failed;
    }

    // if dying already
    PStateFlags pstateflags = XSEItemHandler_Player__M_PLAYERSTATEFLAGS(gpPlayer);
    if ((pstateflags == ps_willdie) || (pstateflags == ps_dead)) {
        return DeathLinkResult_Failed;
    }

    // if can't be attacked
    if (XSEItemHandler_Player__InvulnerableToAttack(gpPlayer, 0)) {
        return DeathLinkResult_Failed;
    }

    // Turret minigame special case
    SE_Map* curr_map = GetSpyroMap(0);
    switch (curr_map->m_MapGeoHashCode) {
        case HT_File_MR1_Spy:
        case HT_File_MR2_Spy:
        case HT_File_MR3_Spy:
        case HT_File_MR4_Spy:
        {
            if (take_butterfly_jar(shielded)) {
                return DeathLinkResult_Shielded;
            }

            // Because deathlink is handled immediately after SetMiniGameFailed:
            deathlink_ignore_next_death = true;

            SEMap_MiniGame__SetMiniGameFailed(curr_map);
            return DeathLinkResult_MiniGameFail;
        }
    }
    
    objCollide obj;
    obj.velocity.x = 0.0f;
    obj.velocity.y = 0.0f;
    obj.velocity.z = 0.0f;
    obj.velocity.w = 0.0f;
    
    Players playertype = XSEItemHandler_Player__M_PLAYERTYPE(gpPlayer);

    // Sgt. Byrd special case
    if (playertype == Player_SrgBird) {
        switch (currmode) {
            case breatheFire: // lava crash (yes really)
            case water_dive: // water crash
            case deathfall: // death fall
                return DeathLinkResult_Failed;
        }

        if (take_butterfly_jar(shielded)) {
            XSEItemHandler_BallGadget__TakeDamage(gpPlayer, 0, 0, 1, &obj, "Death Link", true);
            return DeathLinkResult_Shielded;
        }

        XSEItemHandler_Player__SetMode(gpPlayer, breatheFire, 1, 0);
        return DeathLinkResult_Died;
    }

    // Ball Gadget special case
    if (playertype == Player_BallGadget) {
        // Don't kill if these flags are set (game will probably crash)
        u32* ball_physicsflags = &XSEITEMHANDLER_BALLGADGET_M_PHYSICSFLAGS(gpPlayer);
        if (((*ball_physicsflags) & 0x42) != 0) {
            return DeathLinkResult_Failed;
        }

        if (take_butterfly_jar(shielded)) {
            return DeathLinkResult_Shielded;
        }

        // This physics flag makes the ballgadget killable
        *ball_physicsflags |= 1;
        XSEItemHandler_BallGadget__TakeDamage(gpPlayer, 0xA0, 0, 1, &obj, "Death Link", true);

        return DeathLinkResult_Died;
    }

    // Handle default case (Spyro, Hunter, Blink and Sparx)

    if (take_butterfly_jar(shielded)) {
        XSEItemHandler_Player__TakeDamage(gpPlayer, 0, 0, 1, &obj, "Death Link", true);
        return DeathLinkResult_Shielded;
    } else {
        XSEItemHandler_Player__TakeDamage(gpPlayer, 0xA0, 0, 1, &obj, "Death Link", true);
        return DeathLinkResult_Died;
    }
}

void ap_handle_deathlink_outgoing()
{
    if (deathlink_ignore_next_death) {
        deathlink_ignore_next_death = false;
    } else {
        g_gamestate_ap_settings.deathlink_outgoing = true;
    }
}

bool take_butterfly_jar(bool shielded)
{
    bool had_jar = (gGameState.m_PlayerState.m_AbilityFlags & ABILITY_BUTTERFLY_JAR) != 0;
    gGameState.m_PlayerState.m_AbilityFlags &= ~ABILITY_BUTTERFLY_JAR;

    if (shielded) {
        return had_jar;
    } else {
        return false;
    }
}
