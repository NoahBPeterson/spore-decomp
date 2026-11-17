// Global setter (0x00f48ae0): store the argument in the global at 0x16c8eb8.
#include "game/types.h"

extern uint32_t gValue_f48ae0;   // 0x016c8eb8

// @ 0x00f48ae0
void SetValue_f48ae0(uint32_t value)
{
    gValue_f48ae0 = value;
}
