// Global setter (0x011812c0): store the argument in the global at 0x16f1c60.
#include "game/types.h"

extern uint32_t gValue_11812c0;   // 0x016f1c60

// @ 0x011812c0
void SetValue_11812c0(uint32_t value)
{
    gValue_11812c0 = value;
}
