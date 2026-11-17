// Wrapper (0x00c40a70): call 0xc40430 with both arguments and report success.
#include "game/types.h"

void Callee_c40a70(void* a, void* b);   // 0x00c40430

// @ 0x00c40a70
bool Wrapper_c40a70(void* a, void* b)
{
    Callee_c40a70(a, b);
    return true;
}
