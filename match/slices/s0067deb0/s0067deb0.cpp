// Global setter (0x0067deb0): store the argument in the global at 0x15fd890.
#include "game/types.h"

extern uint32_t gValue_67deb0;   // 0x015fd890

// @ 0x0067deb0
void SetValue_67deb0(uint32_t value)
{
    gValue_67deb0 = value;
}
