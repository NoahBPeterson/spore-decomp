// Global setter (0x0067df00): store the argument in the global at 0x15fd8b0.
#include "game/types.h"

extern uint32_t gValue_67df00;   // 0x015fd8b0

// @ 0x0067df00
void SetValue_67df00(uint32_t value)
{
    gValue_67df00 = value;
}
