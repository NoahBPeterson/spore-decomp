// Global setter (0x00f48ab0): store the argument in the global at 0x16c8eb0.
#include "game/types.h"

extern uint32_t gValue_f48ab0;   // 0x016c8eb0

// @ 0x00f48ab0
void SetValue_f48ab0(uint32_t value)
{
    gValue_f48ab0 = value;
}
