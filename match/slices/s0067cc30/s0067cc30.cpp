// Global setter (0x0067cc30): store the argument in the global at 0x15fcc70.
#include "game/types.h"

extern uint32_t gValue_67cc30;   // 0x015fcc70

// @ 0x0067cc30
void SetValue_67cc30(uint32_t value)
{
    gValue_67cc30 = value;
}
