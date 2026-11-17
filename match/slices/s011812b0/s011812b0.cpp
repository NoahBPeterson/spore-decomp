// Global setter (0x011812b0): store the argument in the global at 0x16f1c5c.
#include "game/types.h"

extern uint32_t gValue_11812b0;   // 0x016f1c5c

// @ 0x011812b0
void SetValue_11812b0(uint32_t value)
{
    gValue_11812b0 = value;
}
