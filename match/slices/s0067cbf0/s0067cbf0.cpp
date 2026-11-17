// Global setter (0x0067cbf0): store the argument in the global at 0x15fcc60.
#include "game/types.h"

extern uint32_t gValue_67cbf0;   // 0x015fcc60

// @ 0x0067cbf0
void SetValue_67cbf0(uint32_t value)
{
    gValue_67cbf0 = value;
}
