// Global setter (0x0067df60): store the argument in the global at 0x15fd8c0.
#include "game/types.h"

extern uint32_t gValue_67df60;   // 0x015fd8c0

// @ 0x0067df60
void SetValue_67df60(uint32_t value)
{
    gValue_67df60 = value;
}
