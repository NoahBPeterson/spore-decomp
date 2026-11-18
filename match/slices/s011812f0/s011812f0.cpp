// Global setter (0x011812f0): store the argument in the global at 0x16f1c58.
#include "game/types.h"

extern uint32_t gValue_11812f0;   // 0x016f1c58

// @ 0x011812f0
void SetValue_11812f0(uint32_t value)
{
    gValue_11812f0 = value;
}
