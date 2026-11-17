// Global setter (0x0067cbe0): store the argument in the global at 0x15fcc5c.
#include "game/types.h"

extern uint32_t gValue_67cbe0;   // 0x015fcc5c

// @ 0x0067cbe0
void SetValue_67cbe0(uint32_t value)
{
    gValue_67cbe0 = value;
}
