// Wrapper (0x00c8ec20): call 0xc8e3a0 with both arguments and report success.
#include "game/types.h"

void Callee_c8ec20(void* a, void* b);   // 0x00c8e3a0

// @ 0x00c8ec20
bool Wrapper_c8ec20(void* a, void* b)
{
    Callee_c8ec20(a, b);
    return true;
}
