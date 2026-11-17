// Global setter (0x0082e4b0): store the argument in the global at 0x164e8f8.
#include "game/types.h"

extern uint32_t gValue_82e4b0;   // 0x0164e8f8

// @ 0x0082e4b0
void SetValue_82e4b0(uint32_t value)
{
    gValue_82e4b0 = value;
}
