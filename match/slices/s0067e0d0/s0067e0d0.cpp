// Global setter (0x0067e0d0): store the argument in the global at 0x15fd914.
#include "game/types.h"

extern uint32_t gValue_67e0d0;   // 0x015fd914

// @ 0x0067e0d0
void SetValue_67e0d0(uint32_t value)
{
    gValue_67e0d0 = value;
}
