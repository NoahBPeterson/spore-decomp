// Wrapper (0x00febfb0): call 0xfebab0 with both arguments and report success.
#include "game/types.h"

void Callee_febfb0(void* a, void* b);   // 0x00febab0

// @ 0x00febfb0
bool Wrapper_febfb0(void* a, void* b)
{
    Callee_febfb0(a, b);
    return true;
}
