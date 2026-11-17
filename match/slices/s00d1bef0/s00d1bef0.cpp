// Global setter (0x00d1bef0): store the argument in the global at 0x169dca0.
#include "game/types.h"

extern uint32_t gValue_d1bef0;   // 0x0169dca0

// @ 0x00d1bef0
void SetValue_d1bef0(uint32_t value)
{
    gValue_d1bef0 = value;
}
