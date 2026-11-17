// Global setter (0x0067e0c0): store the argument in the global at 0x15fd928.
#include "game/types.h"

extern uint32_t gValue_67e0c0;   // 0x015fd928

// @ 0x0067e0c0
void SetValue_67e0c0(uint32_t value)
{
    gValue_67e0c0 = value;
}
