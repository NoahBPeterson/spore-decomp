// Global setter (0x0067cc20): store the argument in the global at 0x15fcc6c.
#include "game/types.h"

extern uint32_t gValue_67cc20;   // 0x015fcc6c

// @ 0x0067cc20
void SetValue_67cc20(uint32_t value)
{
    gValue_67cc20 = value;
}
