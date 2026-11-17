// Global setter (0x00f48ad0): store the argument in the global at 0x16c8eb4.
#include "game/types.h"

extern uint32_t gValue_f48ad0;   // 0x016c8eb4

// @ 0x00f48ad0
void SetValue_f48ad0(uint32_t value)
{
    gValue_f48ad0 = value;
}
