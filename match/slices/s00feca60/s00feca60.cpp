// Wrapper (0x00feca60): call 0xfec3c0 with both arguments and report success.
#include "game/types.h"

void Callee_feca60(void* a, void* b);   // 0x00fec3c0

// @ 0x00feca60
bool Wrapper_feca60(void* a, void* b)
{
    Callee_feca60(a, b);
    return true;
}
