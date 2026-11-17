// Global setter (0x0067ded0): store the argument in the global at 0x15fd898.
#include "game/types.h"

extern uint32_t gValue_67ded0;   // 0x015fd898

// @ 0x0067ded0
void SetValue_67ded0(uint32_t value)
{
    gValue_67ded0 = value;
}
