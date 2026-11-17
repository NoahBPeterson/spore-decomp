// Global setter (0x011e5850): store the argument in the global at 0x16f4aec.
#include "game/types.h"

extern uint32_t gValue_11e5850;   // 0x016f4aec

// @ 0x011e5850
void SetValue_11e5850(uint32_t value)
{
    gValue_11e5850 = value;
}
