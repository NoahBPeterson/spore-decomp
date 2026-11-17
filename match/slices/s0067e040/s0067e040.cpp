// Global setter (0x0067e040): store the argument in the global at 0x15fd8a8.
#include "game/types.h"

extern uint32_t gValue_67e040;   // 0x015fd8a8

// @ 0x0067e040
void SetValue_67e040(uint32_t value)
{
    gValue_67e040 = value;
}
