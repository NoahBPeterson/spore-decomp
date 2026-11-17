// Global setter (0x0067df70): store the argument in the global at 0x15fd8c8.
#include "game/types.h"

extern uint32_t gValue_67df70;   // 0x015fd8c8

// @ 0x0067df70
void SetValue_67df70(uint32_t value)
{
    gValue_67df70 = value;
}
