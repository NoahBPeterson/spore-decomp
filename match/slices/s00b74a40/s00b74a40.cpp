// Wrapper (0x00b74a40): call 0xb73170 with both arguments and report success.
#include "game/types.h"

void Callee_b74a40(void* a, void* b);   // 0x00b73170

// @ 0x00b74a40
bool Wrapper_b74a40(void* a, void* b)
{
    Callee_b74a40(a, b);
    return true;
}
