// Wrapper (0x00c8ec40): call 0xc8e310 with both arguments and report success.
#include "game/types.h"

void Callee_c8ec40(void* a, void* b);   // 0x00c8e310

// @ 0x00c8ec40
bool Wrapper_c8ec40(void* a, void* b)
{
    Callee_c8ec40(a, b);
    return true;
}
