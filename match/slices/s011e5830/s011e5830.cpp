// Global setter (0x011e5830): store the argument in the global at 0x16f4ae4.
#include "game/types.h"

extern uint32_t gValue_11e5830;   // 0x016f4ae4

// @ 0x011e5830
void SetValue_11e5830(uint32_t value)
{
    gValue_11e5830 = value;
}
