// Global setter (0x0067cb90): store the argument in the global at 0x15fcc48.
#include "game/types.h"

extern uint32_t gValue_67cb90;   // 0x015fcc48

// @ 0x0067cb90
void SetValue_67cb90(uint32_t value)
{
    gValue_67cb90 = value;
}
