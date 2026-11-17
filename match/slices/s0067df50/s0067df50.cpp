// Global setter (0x0067df50): store the argument in the global at 0x15fd8bc.
#include "game/types.h"

extern uint32_t gValue_67df50;   // 0x015fd8bc

// @ 0x0067df50
void SetValue_67df50(uint32_t value)
{
    gValue_67df50 = value;
}
