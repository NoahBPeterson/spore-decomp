// Wrapper (0x00c88b80): call 0xc885b0 with both arguments and report success.
#include "game/types.h"

void Callee_c88b80(void* a, void* b);   // 0x00c885b0

// @ 0x00c88b80
bool Wrapper_c88b80(void* a, void* b)
{
    Callee_c88b80(a, b);
    return true;
}
