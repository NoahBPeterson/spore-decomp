// Slice s00e52a40 -- SP cell-game clamp helper: clamp (a + b) between a lower bound of 0 and an
// upper bound of 0x13. The original keeps the selection in eax and re-tests through the pointer
// (`lea eax,[&lo]; js; lea eax,[&sum]; cmp [eax],0x13; jle; lea eax,[&hi]; mov eax,[eax]`),
// reusing the argument homes for sum/lo (frameless, `push ecx`).
//   * `sum` must be written first, then `upper`, then the lower bound (the original's store order);
//     the lower bound is the (overwritten) second parameter home, so `b = 0` and `&b` reproduce the
//     original's [esp+0xc] slot.
//   * `_ReadWriteBarrier()` stops cl from CSE-ing *p with sum, keeping the compare a memory operand.
//   * the `if (sum < 0) ... else ...` order is what puts the pointer in eax and shares the tail.
// Flags: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"
#include <intrin.h>

// @ 0x00e52a40
int FUN_00e52a40(int a, int b)
{
    int sum = a + b;
    int upper = 0x13;
    b = 0;                          // reuse the parameter home as the lower bound
    int* p;
    if (sum < 0)
        p = &b;
    else
        p = &sum;
    _ReadWriteBarrier();
    if (*p > upper)
        p = &upper;
    return *p;
}
