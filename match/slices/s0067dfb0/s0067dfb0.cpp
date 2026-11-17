// Global setter (0x0067dfb0): store the argument in the global at 0x15fd8d4.
#include "game/types.h"

extern uint32_t gValue_67dfb0;   // 0x015fd8d4

// @ 0x0067dfb0
void SetValue_67dfb0(uint32_t value)
{
    gValue_67dfb0 = value;
}
