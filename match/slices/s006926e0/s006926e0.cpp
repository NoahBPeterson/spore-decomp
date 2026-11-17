// Global setter (0x006926e0): store the argument in the global at 0x1600778.
#include "game/types.h"

extern uint32_t gValue_6926e0;   // 0x01600778

// @ 0x006926e0
void SetValue_6926e0(uint32_t value)
{
    gValue_6926e0 = value;
}
