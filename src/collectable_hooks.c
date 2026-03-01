#include <collectable_hooks.h>
#include <ap_collectables.h>

void LightXtal__Collected_VtableHook(void *this, Bool Register)
{
    LightXtal__Collected(this, Register);
}

void DragonEgg__Collected_VtableHook(void *this, Bool Register)
{
    DragonEgg__Collected(this, Register);
}

void DarkXtal__Collected_VtableHook(void *this, Bool Register)
{
    DarkXtal__Collected(this, Register);
}

void register_collectable(void* special_item, APCollectable_Type type)
{

}

int binary_search_for_collectable(u16 map_index, u16 trigger_index)
{
    int start = AP_GRABBABLE_START;
    int end = AP_GRABBABLE_START + AP_GRABBABLE_NUM - 1;

    while (start <= end) {
        int index = start + ((end-start)/2);
        APCollectable* curr = &g_ap_collectables[index];

        if ((map_index == curr->grabbable.map_index) &&
            (trigger_index == curr->grabbable.trigger_index)) {
            return index;
        }

        if ((map_index < curr->grabbable.map_index) ||
            ((map_index == curr->grabbable.map_index) &&
            (trigger_index < curr->grabbable.trigger_index))) {
            end = index - 1;
        } else {
            start = index + 1;
        }
    }

    return -1;
}
