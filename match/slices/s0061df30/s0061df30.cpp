// Global setter (0x0061df30): store the argument in the global at 0x15f5628.
#include "game/types.h"

extern uint32_t gValue_61df30;   // 0x015f5628

// @ 0x0061df30
void SetValue_61df30(uint32_t value)
{
    gValue_61df30 = value;
}
