// Wrapper (0x00f26aa0): call 0xf25e00 with both arguments and report success.
#include "game/types.h"

void Callee_f26aa0(void* a, void* b);   // 0x00f25e00

// @ 0x00f26aa0
bool Wrapper_f26aa0(void* a, void* b)
{
    Callee_f26aa0(a, b);
    return true;
}
