// Global setter (0x0067cbc0): store the argument in the global at 0x15fcc54.
#include "game/types.h"

extern uint32_t gValue_67cbc0;   // 0x015fcc54

// @ 0x0067cbc0
void SetValue_67cbc0(uint32_t value)
{
    gValue_67cbc0 = value;
}
