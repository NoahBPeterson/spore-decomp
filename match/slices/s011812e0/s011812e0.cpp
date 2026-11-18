// Global setter (0x011812e0): store the argument in the global at 0x16f1c50.
#include "game/types.h"

extern uint32_t gValue_11812e0;   // 0x016f1c50

// @ 0x011812e0
void SetValue_11812e0(uint32_t value)
{
    gValue_11812e0 = value;
}
