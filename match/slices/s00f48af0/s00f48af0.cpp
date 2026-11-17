// Global setter (0x00f48af0): store the argument in the global at 0x16c8ebc.
#include "game/types.h"

extern uint32_t gValue_f48af0;   // 0x016c8ebc

// @ 0x00f48af0
void SetValue_f48af0(uint32_t value)
{
    gValue_f48af0 = value;
}
