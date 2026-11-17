// Global setter (0x0067cc00): store the argument in the global at 0x15fcc64.
#include "game/types.h"

extern uint32_t gValue_67cc00;   // 0x015fcc64

// @ 0x0067cc00
void SetValue_67cc00(uint32_t value)
{
    gValue_67cc00 = value;
}
