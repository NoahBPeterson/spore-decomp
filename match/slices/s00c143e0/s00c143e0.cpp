// Wrapper (0x00c143e0): call 0xc0fda0 with both arguments and report success.
#include "game/types.h"

void Callee_c143e0(void* a, void* b);   // 0x00c0fda0

// @ 0x00c143e0
bool Wrapper_c143e0(void* a, void* b)
{
    Callee_c143e0(a, b);
    return true;
}
