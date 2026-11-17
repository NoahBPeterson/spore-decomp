// Global setter (0x0067df20): store the argument in the global at 0x15fd920.
#include "game/types.h"

extern uint32_t gValue_67df20;   // 0x015fd920

// @ 0x0067df20
void SetValue_67df20(uint32_t value)
{
    gValue_67df20 = value;
}
