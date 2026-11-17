// Wrapper (0x00c88b60): call 0xc88610 with both arguments and report success.
#include "game/types.h"

void Callee_c88b60(void* a, void* b);   // 0x00c88610

// @ 0x00c88b60
bool Wrapper_c88b60(void* a, void* b)
{
    Callee_c88b60(a, b);
    return true;
}
