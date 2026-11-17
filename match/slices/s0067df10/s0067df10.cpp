// Global setter (0x0067df10): store the argument in the global at 0x15fd91c.
#include "game/types.h"

extern uint32_t gValue_67df10;   // 0x015fd91c

// @ 0x0067df10
void SetValue_67df10(uint32_t value)
{
    gValue_67df10 = value;
}
