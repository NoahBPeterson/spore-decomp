// Wrapper (0x00d010f0): call 0xd00c70 with both arguments and report success.
#include "game/types.h"

void Callee_d010f0(void* a, void* b);   // 0x00d00c70

// @ 0x00d010f0
bool Wrapper_d010f0(void* a, void* b)
{
    Callee_d010f0(a, b);
    return true;
}
