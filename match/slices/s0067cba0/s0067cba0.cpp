// Global setter (0x0067cba0): store the argument in the global at 0x15fcc4c.
#include "game/types.h"

extern uint32_t gValue_67cba0;   // 0x015fcc4c

// @ 0x0067cba0
void SetValue_67cba0(uint32_t value)
{
    gValue_67cba0 = value;
}
