// Global setter (0x0067cc60): store the argument in the global at 0x15fcc80.
#include "game/types.h"

extern uint32_t gValue_67cc60;   // 0x015fcc80

// @ 0x0067cc60
void SetValue_67cc60(uint32_t value)
{
    gValue_67cc60 = value;
}
