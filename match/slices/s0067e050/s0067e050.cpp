// Global setter (0x0067e050): store the argument in the global at 0x15fd918.
#include "game/types.h"

extern uint32_t gValue_67e050;   // 0x015fd918

// @ 0x0067e050
void SetValue_67e050(uint32_t value)
{
    gValue_67e050 = value;
}
