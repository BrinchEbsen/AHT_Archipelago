#include <ap_warps.h>
#include <gameloop.h>
#include <map.h>
#include <player.h>
#include <pad.h>

bool draw_warp_text = false;

WarpNode warp_nodes[WARP_NODES_COUNT] =
{
    // [0] Cloudy Domain start of orbiting platforms 1
    {
        .pos = {
            .x = 66.6408997f,
            .y = 17.3519592f,
            .z = -125.40934f
        },
        .radius = DEFAULT_WARP_NODE_RADIUS,
        .map_index = 20,
        .warp_to_index = 1
    },
    // [1] Cloudy Domain end of orbiting platforms 1
    {
        .pos = {
            .x = 160.227051f,
            .y = 16.3142719f,
            .z = -311.541138f
        },
        .radius = DEFAULT_WARP_NODE_RADIUS,
        .map_index = 20,
        .warp_to_index = 0
    },
    // [2] Cloudy Domain start of orbiting platforms 2
    {
        .pos = {
            .x = 204.552109f,
            .y = 16.3116283f,
            .z = -308.00354f
        },
        .radius = DEFAULT_WARP_NODE_RADIUS,
        .map_index = 20,
        .warp_to_index = 3
    },
    // [3] Cloudy Domain end of orbiting platforms 2
    {
        .pos = {
            .x = 233.433655f,
            .y = 17.3269253f,
            .z = -192.885864f
        },
        .radius = DEFAULT_WARP_NODE_RADIUS,
        .map_index = 20,
        .warp_to_index = 2
    }
};

void ap_warps_update()
{
    draw_warp_text = false;

    if ((gGameLoop.m_State != Running) || gGameLoop.m_GameIsPaused)
    {
        return;
    }

    if (gpPlayer == NULL)
    {
        return;
    }

    SE_Map* map = GetSpyroMap(0);
    if (map == NULL)
    {
        return;
    }

    for (int i = 0; i < WARP_NODES_COUNT; i++)
    {
        WarpNode* wn = &warp_nodes[i];

        if (map->m_MapListIndex != wn->map_index)
        {
            continue;
        }
        
        // Check if the player is in range.

        EXVector* player_pos = OFFSET_PTR(EXVector, gpPlayerItem, 0xD0);

        float dx = player_pos->x - wn->pos.x;
        float dy = player_pos->y - wn->pos.y;
        float dz = player_pos->z - wn->pos.z;

        float axis_sqr = (dx*dx) + (dy*dy) + (dz*dz);
        float radius_sqr = wn->radius*wn->radius;

        if (axis_sqr > radius_sqr)
        {
            continue;
        }

        draw_warp_text = true;

        if (g_pad_button_edge_down(PAD_BUTTON_B))
        {
            EXVector* player_rot = OFFSET_PTR(EXVector, gpPlayerItem, 0xE0);

            EXVector warp_to = {
                .x = warp_nodes[wn->warp_to_index].pos.x,
                .y = warp_nodes[wn->warp_to_index].pos.y,
                .z = warp_nodes[wn->warp_to_index].pos.z,
                0.0f
            };

            XSEItemHandler_Player__SetPlayer(gpPlayer, &warp_to, player_rot);
        }

        break;
    }
}
