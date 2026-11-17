// Wrapper (0x00c31c80): call 0xc30fe0 with both arguments and report success.
#include "game/types.h"

void Callee_c31c80(void* a, void* b);   // 0x00c30fe0

// @ 0x00c31c80
bool Wrapper_c31c80(void* a, void* b)
{
    Callee_c31c80(a, b);
    return true;
}
