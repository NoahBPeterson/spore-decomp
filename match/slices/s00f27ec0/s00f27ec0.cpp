// Wrapper (0x00f27ec0): call 0xf27370 with both arguments and report success.
#include "game/types.h"

void Callee_f27ec0(void* a, void* b);   // 0x00f27370

// @ 0x00f27ec0
bool Wrapper_f27ec0(void* a, void* b)
{
    Callee_f27ec0(a, b);
    return true;
}
