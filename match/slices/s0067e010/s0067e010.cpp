// Global setter (0x0067e010): store the argument in the global at 0x15fd8f0.
#include "game/types.h"

extern uint32_t gValue_67e010;   // 0x015fd8f0

// @ 0x0067e010
void SetValue_67e010(uint32_t value)
{
    gValue_67e010 = value;
}
