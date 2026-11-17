// Wrapper (0x00b26990): call 0xb318d0 with both arguments and report success.
#include "game/types.h"

void Callee_b26990(void* a, void* b);   // 0x00b318d0

// @ 0x00b26990
bool Wrapper_b26990(void* a, void* b)
{
    Callee_b26990(a, b);
    return true;
}
