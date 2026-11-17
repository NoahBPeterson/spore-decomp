// Global setter (0x0067df40): store the argument in the global at 0x15fd8b8.
#include "game/types.h"

extern uint32_t gValue_67df40;   // 0x015fd8b8

// @ 0x0067df40
void SetValue_67df40(uint32_t value)
{
    gValue_67df40 = value;
}
