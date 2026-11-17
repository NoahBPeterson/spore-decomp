// Wrapper (0x00b00430): call 0xaffbf0 with both arguments and report success.
#include "game/types.h"

void Callee_b00430(void* a, void* b);   // 0x00affbf0

// @ 0x00b00430
bool Wrapper_b00430(void* a, void* b)
{
    Callee_b00430(a, b);
    return true;
}
