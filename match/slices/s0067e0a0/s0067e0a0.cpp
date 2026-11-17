// Global setter (0x0067e0a0): store the argument in the global at 0x15fd90c.
#include "game/types.h"

extern uint32_t gValue_67e0a0;   // 0x015fd90c

// @ 0x0067e0a0
void SetValue_67e0a0(uint32_t value)
{
    gValue_67e0a0 = value;
}
