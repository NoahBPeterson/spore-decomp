// Global setter (0x009512b0): store the argument in the global at 0x166aab4.
#include "game/types.h"

extern uint32_t gValue_9512b0;   // 0x0166aab4

// @ 0x009512b0
void SetValue_9512b0(uint32_t value)
{
    gValue_9512b0 = value;
}
