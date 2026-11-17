// Global setter (0x0067dfe0): store the argument in the global at 0x15fd8e0.
#include "game/types.h"

extern uint32_t gValue_67dfe0;   // 0x015fd8e0

// @ 0x0067dfe0
void SetValue_67dfe0(uint32_t value)
{
    gValue_67dfe0 = value;
}
