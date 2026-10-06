// Batch bfs4 slice s01212800, 0x01212800-0x01213e30.
//
// Almost every VA is a compiler-generated MSVC EH cleanup funclet: the entry reads the
// caller's frame through EBP ([ebp-N] / [ebp+4]) and tail-jumps into RAII destructors or
// operator_delete. 0x012138a0 is a genuine leaf that clears bit 0 of a global flag.
#include "types.h"
typedef unsigned int u32;

extern volatile u32 g_16f33b78;   // 0x1633b78 (retail address)

// @ 0x012138a0
void __cdecl ClearFlagBit0()
{
    u32 v = g_16f33b78;
    g_16f33b78 = v & 0xfffffffeu;
}

// @ 0x01212800
void __cdecl FUN_01212800() {}
// @ 0x012129a0
void __cdecl FUN_012129a0() {}
// @ 0x012129d0
void __cdecl FUN_012129d0() {}
// @ 0x01212a70
void __cdecl FUN_01212a70() {}
// @ 0x01212d70
void __cdecl FUN_01212d70() {}
// @ 0x01212dc0
void __cdecl FUN_01212dc0() {}
// @ 0x01212e30
void __cdecl FUN_01212e30() {}
// @ 0x01212f00
void __cdecl FUN_01212f00() {}
// @ 0x01212f30
void __cdecl FUN_01212f30() {}
// @ 0x01213000
void __cdecl FUN_01213000() {}
// @ 0x012130b0
void __cdecl FUN_012130b0() {}
// @ 0x01213150
void __cdecl FUN_01213150() {}
// @ 0x012131c0
void __cdecl FUN_012131c0() {}
// @ 0x01213230
void __cdecl FUN_01213230() {}
// @ 0x01213280
void __cdecl FUN_01213280() {}
// @ 0x012132b0
void __cdecl FUN_012132b0() {}
// @ 0x01213340
void __cdecl FUN_01213340() {}
// @ 0x012133a0
void __cdecl FUN_012133a0() {}
// @ 0x01213440
void __cdecl FUN_01213440() {}
// @ 0x012134e0
void __cdecl FUN_012134e0() {}
// @ 0x01213630
void __cdecl FUN_01213630() {}
// @ 0x012136b0
void __cdecl FUN_012136b0() {}
// @ 0x01213750
void __cdecl FUN_01213750() {}
// @ 0x012137f0
void __cdecl FUN_012137f0() {}
// @ 0x012138e0
void __cdecl FUN_012138e0() {}
// @ 0x01213930
void __cdecl FUN_01213930() {}
// @ 0x01213a10
void __cdecl FUN_01213a10() {}
// @ 0x01213a70
void __cdecl FUN_01213a70() {}
// @ 0x01213ae0
void __cdecl FUN_01213ae0() {}
// @ 0x01213b70
void __cdecl FUN_01213b70() {}
// @ 0x01213bb0
void __cdecl FUN_01213bb0() {}
// @ 0x01213be0
void __cdecl FUN_01213be0() {}
// @ 0x01213d10
void __cdecl FUN_01213d10() {}
// @ 0x01213e30
void __cdecl FUN_01213e30() {}
