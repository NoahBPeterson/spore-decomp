// Wrapper (0x00b26970): call 0xb31780 with both arguments and report success.
#include "game/types.h"

void Callee_b26970(void* a, void* b);   // 0x00b31780

// @ 0x00b26970
bool Wrapper_b26970(void* a, void* b)
{
    Callee_b26970(a, b);
    return true;
}
