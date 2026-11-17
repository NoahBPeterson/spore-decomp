// Global setter (0x0067cc40): store the argument in the global at 0x15fcc74.
#include "game/types.h"

extern uint32_t gValue_67cc40;   // 0x015fcc74

// @ 0x0067cc40
void SetValue_67cc40(uint32_t value)
{
    gValue_67cc40 = value;
}
