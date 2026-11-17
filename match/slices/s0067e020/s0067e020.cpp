// Global setter (0x0067e020): store the argument in the global at 0x15fd8f4.
#include "game/types.h"

extern uint32_t gValue_67e020;   // 0x015fd8f4

// @ 0x0067e020
void SetValue_67e020(uint32_t value)
{
    gValue_67e020 = value;
}
