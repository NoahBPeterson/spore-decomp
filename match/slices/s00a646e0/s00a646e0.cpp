// Global setter (0x00a646e0): store the argument in the global at 0x15544bc.
#include "game/types.h"

extern uint32_t gValue_a646e0;   // 0x015544bc

// @ 0x00a646e0
void SetValue_a646e0(uint32_t value)
{
    gValue_a646e0 = value;
}
