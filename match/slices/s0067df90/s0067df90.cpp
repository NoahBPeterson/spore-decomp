// Global setter (0x0067df90): store the argument in the global at 0x15fd8cc.
#include "game/types.h"

extern uint32_t gValue_67df90;   // 0x015fd8cc

// @ 0x0067df90
void SetValue_67df90(uint32_t value)
{
    gValue_67df90 = value;
}
