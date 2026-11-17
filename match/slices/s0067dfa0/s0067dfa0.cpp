// Global setter (0x0067dfa0): store the argument in the global at 0x15fd8d0.
#include "game/types.h"

extern uint32_t gValue_67dfa0;   // 0x015fd8d0

// @ 0x0067dfa0
void SetValue_67dfa0(uint32_t value)
{
    gValue_67dfa0 = value;
}
