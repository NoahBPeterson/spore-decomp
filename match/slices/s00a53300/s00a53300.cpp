// Global setter (0x00a53300): store the argument in the global at 0x1675560.
#include "game/types.h"

extern uint32_t gValue_a53300;   // 0x01675560

// @ 0x00a53300
void SetValue_a53300(uint32_t value)
{
    gValue_a53300 = value;
}
