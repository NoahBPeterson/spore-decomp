// Global setter (0x00f48ac0): store the argument in the global at 0x16c8eac.
#include "game/types.h"

extern uint32_t gValue_f48ac0;   // 0x016c8eac

// @ 0x00f48ac0
void SetValue_f48ac0(uint32_t value)
{
    gValue_f48ac0 = value;
}
