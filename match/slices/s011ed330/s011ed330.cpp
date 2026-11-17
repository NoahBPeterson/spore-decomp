// Global setter (0x011ed330): store the argument in the global at 0x16f5bd4.
#include "game/types.h"

extern uint32_t gValue_11ed330;   // 0x016f5bd4

// @ 0x011ed330
void SetValue_11ed330(uint32_t value)
{
    gValue_11ed330 = value;
}
