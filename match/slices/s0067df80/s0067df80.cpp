// Global setter (0x0067df80): store the argument in the global at 0x15fd8c4.
#include "game/types.h"

extern uint32_t gValue_67df80;   // 0x015fd8c4

// @ 0x0067df80
void SetValue_67df80(uint32_t value)
{
    gValue_67df80 = value;
}
