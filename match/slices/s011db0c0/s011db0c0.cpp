// Global setter (0x011db0c0): store the argument in the global at 0x16f2340.
#include "game/types.h"

extern uint32_t gValue_11db0c0;   // 0x016f2340

// @ 0x011db0c0
void SetValue_11db0c0(uint32_t value)
{
    gValue_11db0c0 = value;
}
