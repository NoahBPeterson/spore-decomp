// Global setter (0x011ed320): store the argument in the global at 0x16f5bd0.
#include "game/types.h"

extern uint32_t gValue_11ed320;   // 0x016f5bd0

// @ 0x011ed320
void SetValue_11ed320(uint32_t value)
{
    gValue_11ed320 = value;
}
