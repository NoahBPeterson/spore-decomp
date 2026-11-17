// Global setter (0x0067cbd0): store the argument in the global at 0x15fcc58.
#include "game/types.h"

extern uint32_t gValue_67cbd0;   // 0x015fcc58

// @ 0x0067cbd0
void SetValue_67cbd0(uint32_t value)
{
    gValue_67cbd0 = value;
}
