// Wrapper (0x00ae3430): call 0xae2ed0 with both arguments and report success.
#include "game/types.h"

void Callee_ae3430(void* a, void* b);   // 0x00ae2ed0

// @ 0x00ae3430
bool Wrapper_ae3430(void* a, void* b)
{
    Callee_ae3430(a, b);
    return true;
}
