// Global setter (0x011e5840): store the argument in the global at 0x16f4ae8.
#include "game/types.h"

extern uint32_t gValue_11e5840;   // 0x016f4ae8

// @ 0x011e5840
void SetValue_11e5840(uint32_t value)
{
    gValue_11e5840 = value;
}
