// Global setter (0x0067dff0): store the argument in the global at 0x15fd8e8.
#include "game/types.h"

extern uint32_t gValue_67dff0;   // 0x015fd8e8

// @ 0x0067dff0
void SetValue_67dff0(uint32_t value)
{
    gValue_67dff0 = value;
}
