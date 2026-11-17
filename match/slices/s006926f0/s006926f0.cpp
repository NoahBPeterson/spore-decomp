// Global setter (0x006926f0): store the argument in the global at 0x160077c.
#include "game/types.h"

extern uint32_t gValue_6926f0;   // 0x0160077c

// @ 0x006926f0
void SetValue_6926f0(uint32_t value)
{
    gValue_6926f0 = value;
}
