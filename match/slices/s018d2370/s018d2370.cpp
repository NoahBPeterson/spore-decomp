// Slice s018d2370: a /Od module stub -- a three-argument __stdcall routine whose
// body is just `return 0`.  At /Od the compiler still sets up the frame pointer,
// which is why the 9-byte original is `push ebp; mov ebp,esp; xor eax,eax;
// pop ebp; ret 0xc` and not the 5-byte /O2 leaf.
// Flags: /Od /MD /Gy /EHsc /TP
#include "types.h"

// @ 0x018d2370
int __stdcall stub_018d2370(int a, int b, int c)
{
    return 0;
}
