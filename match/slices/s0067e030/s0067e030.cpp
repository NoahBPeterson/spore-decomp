// Global setter (0x0067e030): store the argument in the global at 0x15fd8a4.
#include "game/types.h"

extern uint32_t gValue_67e030;   // 0x015fd8a4

// @ 0x0067e030
void SetValue_67e030(uint32_t value)
{
    gValue_67e030 = value;
}
