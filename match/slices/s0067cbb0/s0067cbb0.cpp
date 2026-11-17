// Global setter (0x0067cbb0): store the argument in the global at 0x15fcc50.
#include "game/types.h"

extern uint32_t gValue_67cbb0;   // 0x015fcc50

// @ 0x0067cbb0
void SetValue_67cbb0(uint32_t value)
{
    gValue_67cbb0 = value;
}
