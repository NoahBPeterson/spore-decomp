// Global setter (0x011f8110): store the argument in the global at 0x16f658c.
#include "game/types.h"

extern uint32_t gValue_11f8110;   // 0x016f658c

// @ 0x011f8110
void SetValue_11f8110(uint32_t value)
{
    gValue_11f8110 = value;
}
