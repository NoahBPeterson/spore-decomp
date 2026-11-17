// Global setter (0x00b6e1f0): store the argument in the global at 0x156b018.
#include "game/types.h"

extern uint32_t gValue_b6e1f0;   // 0x0156b018

// @ 0x00b6e1f0
void SetValue_b6e1f0(uint32_t value)
{
    gValue_b6e1f0 = value;
}
