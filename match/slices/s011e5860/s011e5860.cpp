// Global setter (0x011e5860): store the argument in the global at 0x16f4af4.
#include "game/types.h"

extern uint32_t gValue_11e5860;   // 0x016f4af4

// @ 0x011e5860
void SetValue_11e5860(uint32_t value)
{
    gValue_11e5860 = value;
}
