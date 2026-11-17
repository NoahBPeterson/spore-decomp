// Global setter (0x011812d0): store the argument in the global at 0x16f1c64.
#include "game/types.h"

extern uint32_t gValue_11812d0;   // 0x016f1c64

// @ 0x011812d0
void SetValue_11812d0(uint32_t value)
{
    gValue_11812d0 = value;
}
