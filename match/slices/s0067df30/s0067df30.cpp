// Global setter (0x0067df30): store the argument in the global at 0x15fd8b4.
#include "game/types.h"

extern uint32_t gValue_67df30;   // 0x015fd8b4

// @ 0x0067df30
void SetValue_67df30(uint32_t value)
{
    gValue_67df30 = value;
}
