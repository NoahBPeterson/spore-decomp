// Global setter (0x0067dec0): store the argument in the global at 0x15fd894.
#include "game/types.h"

extern uint32_t gValue_67dec0;   // 0x015fd894

// @ 0x0067dec0
void SetValue_67dec0(uint32_t value)
{
    gValue_67dec0 = value;
}
