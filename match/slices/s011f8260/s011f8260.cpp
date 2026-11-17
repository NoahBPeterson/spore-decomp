// Global setter (0x011f8260): store the argument in the global at 0x1712434.
#include "game/types.h"

extern uint32_t gValue_11f8260;   // 0x01712434

// @ 0x011f8260
void SetValue_11f8260(uint32_t value)
{
    gValue_11f8260 = value;
}
