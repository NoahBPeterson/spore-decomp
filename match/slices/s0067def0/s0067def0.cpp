// Global setter (0x0067def0): store the argument in the global at 0x15fd8ac.
#include "game/types.h"

extern uint32_t gValue_67def0;   // 0x015fd8ac

// @ 0x0067def0
void SetValue_67def0(uint32_t value)
{
    gValue_67def0 = value;
}
