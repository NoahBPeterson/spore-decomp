// Wrapper (0x00b02570): call 0xb00760 with both arguments and report success.
#include "game/types.h"

void Callee_b02570(void* a, void* b);   // 0x00b00760

// @ 0x00b02570
bool Wrapper_b02570(void* a, void* b)
{
    Callee_b02570(a, b);
    return true;
}
