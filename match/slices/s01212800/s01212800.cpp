// 0x012138a0 -- clear bit 0 of the global flag word.
//
// Body (14 bytes) is byte-exact: load the word, AND ~1, store it back.
// The retail SYMBOL is 24 bytes because the original had a C++ EH rethrow
// funclet after the ret (mov eax, [type]; jmp __CxxThrowException): the source
// that produces it needs a try block cl cannot prove non-throwing, which a
// volatile load/AND/store never is.  See nonmatching.txt.
#include "types.h"

extern volatile uint32_t g_16f33b78;   // 0x1633b78 (retail address)

// @ 0x012138a0
void __cdecl ClearFlagBit0()
{
    uint32_t v = g_16f33b78;
    g_16f33b78 = v & 0xfffffffeu;
}
