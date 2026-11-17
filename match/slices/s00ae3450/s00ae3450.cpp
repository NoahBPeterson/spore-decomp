// Wrapper (0x00ae3450): call 0xae2e40 with both arguments and report success.
#include "game/types.h"

void Callee_ae3450(void* a, void* b);   // 0x00ae2e40

// @ 0x00ae3450
bool Wrapper_ae3450(void* a, void* b)
{
    Callee_ae3450(a, b);
    return true;
}
