#ifndef AP_WARPS_H
#define AP_WARPS_H
#include <types.h>
#include <exvector.h>

extern bool draw_warp_text;

// A place where the player can stand, press a button, and warp to another node.
typedef struct WarpNode
{
    // The position of the node (and where the player will be placed if warping to this node).
    EXVector3 pos;
    // How close the player needs to be to the node to activate it.
    float radius;
    // The map the node is used in.
    u16 map_index;
    // The node this node connects to (where the player warps to).
    u16 warp_to_index;
} WarpNode;

#define WARP_NODES_COUNT 4
#define DEFAULT_WARP_NODE_RADIUS 5.0f
// The list of warp nodes.
extern WarpNode warp_nodes[WARP_NODES_COUNT];

// Main update routine for warp nodes.
void ap_warps_update();

#endif /* AP_WARPS_H */