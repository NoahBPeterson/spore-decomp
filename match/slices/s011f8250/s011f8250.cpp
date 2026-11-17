// Global setter (0x011f8250): store the argument in the global at 0x1712430.
#include "game/types.h"

extern uint32_t gValue_11f8250;   // 0x01712430

// @ 0x011f8250
void SetValue_11f8250(uint32_t value)
{
    gValue_11f8250 = value;
}
