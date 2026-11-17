// Wrapper (0x00d00c50): call 0xd00900 with both arguments and report success.
#include "game/types.h"

void Callee_d00c50(void* a, void* b);   // 0x00d00900

// @ 0x00d00c50
bool Wrapper_d00c50(void* a, void* b)
{
    Callee_d00c50(a, b);
    return true;
}
