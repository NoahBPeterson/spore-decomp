// Global setter (0x0067e000): store the argument in the global at 0x15fd8ec.
#include "game/types.h"

extern uint32_t gValue_67e000;   // 0x015fd8ec

// @ 0x0067e000
void SetValue_67e000(uint32_t value)
{
    gValue_67e000 = value;
}
