// Global setter (0x0067cc50): store the argument in the global at 0x15fcc78.
#include "game/types.h"

extern uint32_t gValue_67cc50;   // 0x015fcc78

// @ 0x0067cc50
void SetValue_67cc50(uint32_t value)
{
    gValue_67cc50 = value;
}
