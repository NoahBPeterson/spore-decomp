// Global setter (0x0067e080): store the argument in the global at 0x15fd900.
#include "game/types.h"

extern uint32_t gValue_67e080;   // 0x015fd900

// @ 0x0067e080
void SetValue_67e080(uint32_t value)
{
    gValue_67e080 = value;
}
