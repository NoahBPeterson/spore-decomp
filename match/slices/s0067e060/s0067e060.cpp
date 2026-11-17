// Global setter (0x0067e060): store the argument in the global at 0x15fd8f8.
#include "game/types.h"

extern uint32_t gValue_67e060;   // 0x015fd8f8

// @ 0x0067e060
void SetValue_67e060(uint32_t value)
{
    gValue_67e060 = value;
}
