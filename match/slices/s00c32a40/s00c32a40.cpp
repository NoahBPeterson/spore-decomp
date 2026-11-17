// Wrapper (0x00c32a40): call 0xc31cc0 with both arguments and report success.
#include "game/types.h"

void Callee_c32a40(void* a, void* b);   // 0x00c31cc0

// @ 0x00c32a40
bool Wrapper_c32a40(void* a, void* b)
{
    Callee_c32a40(a, b);
    return true;
}
