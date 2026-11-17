// Global setter (0x0067dfc0): store the argument in the global at 0x15fd8d8.
#include "game/types.h"

extern uint32_t gValue_67dfc0;   // 0x015fd8d8

// @ 0x0067dfc0
void SetValue_67dfc0(uint32_t value)
{
    gValue_67dfc0 = value;
}
