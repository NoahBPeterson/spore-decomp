// Wrapper (0x00b72e30): call 0xb72480 with both arguments and report success.
#include "game/types.h"

void Callee_b72e30(void* a, void* b);   // 0x00b72480

// @ 0x00b72e30
bool Wrapper_b72e30(void* a, void* b)
{
    Callee_b72e30(a, b);
    return true;
}
