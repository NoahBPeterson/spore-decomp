// Wrapper (0x00c40a50): call 0xc40390 with both arguments and report success.
#include "game/types.h"

void Callee_c40a50(void* a, void* b);   // 0x00c40390

// @ 0x00c40a50
bool Wrapper_c40a50(void* a, void* b)
{
    Callee_c40a50(a, b);
    return true;
}
