// Global setter (0x0067cc10): store the argument in the global at 0x15fcc68.
#include "game/types.h"

extern uint32_t gValue_67cc10;   // 0x015fcc68

// @ 0x0067cc10
void SetValue_67cc10(uint32_t value)
{
    gValue_67cc10 = value;
}
