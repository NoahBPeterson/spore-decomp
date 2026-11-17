// Global setter (0x0067e070): store the argument in the global at 0x15fd8fc.
#include "game/types.h"

extern uint32_t gValue_67e070;   // 0x015fd8fc

// @ 0x0067e070
void SetValue_67e070(uint32_t value)
{
    gValue_67e070 = value;
}
