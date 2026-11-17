// Global setter (0x011f8ae0): store the argument in the global at 0x15d092c.
#include "game/types.h"

extern uint32_t gValue_11f8ae0;   // 0x015d092c

// @ 0x011f8ae0
void SetValue_11f8ae0(uint32_t value)
{
    gValue_11f8ae0 = value;
}
