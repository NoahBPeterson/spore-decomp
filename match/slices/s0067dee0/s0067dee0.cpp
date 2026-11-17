// Global setter (0x0067dee0): store the argument in the global at 0x15fd89c.
#include "game/types.h"

extern uint32_t gValue_67dee0;   // 0x015fd89c

// @ 0x0067dee0
void SetValue_67dee0(uint32_t value)
{
    gValue_67dee0 = value;
}
