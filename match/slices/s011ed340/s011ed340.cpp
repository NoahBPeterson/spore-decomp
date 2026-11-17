// Global setter (0x011ed340): store the argument in the global at 0x16f5bd8.
#include "game/types.h"

extern uint32_t gValue_11ed340;   // 0x016f5bd8

// @ 0x011ed340
void SetValue_11ed340(uint32_t value)
{
    gValue_11ed340 = value;
}
