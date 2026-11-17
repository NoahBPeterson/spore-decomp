// Wrapper (0x00c143c0): call 0xc0fcf0 with both arguments and report success.
#include "game/types.h"

void Callee_c143c0(void* a, void* b);   // 0x00c0fcf0

// @ 0x00c143c0
bool Wrapper_c143c0(void* a, void* b)
{
    Callee_c143c0(a, b);
    return true;
}
