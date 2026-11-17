// Global setter (0x0067e0b0): store the argument in the global at 0x15fd910.
#include "game/types.h"

extern uint32_t gValue_67e0b0;   // 0x015fd910

// @ 0x0067e0b0
void SetValue_67e0b0(uint32_t value)
{
    gValue_67e0b0 = value;
}
