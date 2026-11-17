// Global setter (0x00989650): store the argument in the global at 0x166b210.
#include "game/types.h"

extern uint32_t gValue_989650;   // 0x0166b210

// @ 0x00989650
void SetValue_989650(uint32_t value)
{
    gValue_989650 = value;
}
