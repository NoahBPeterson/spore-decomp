// Global setter (0x0067dfd0): store the argument in the global at 0x15fd8dc.
#include "game/types.h"

extern uint32_t gValue_67dfd0;   // 0x015fd8dc

// @ 0x0067dfd0
void SetValue_67dfd0(uint32_t value)
{
    gValue_67dfd0 = value;
}
