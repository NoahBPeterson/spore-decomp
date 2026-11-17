// copy_backward (0x00a6a7d0): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xa69e50).
#include "game/types.h"

struct Elem_a6a7d0 {
    char mData[0x14];
    Elem_a6a7d0& operator=(const Elem_a6a7d0& o);   // 0x00a69e50
};

// @ 0x00a6a7d0
Elem_a6a7d0* CopyBackward_a6a7d0(const Elem_a6a7d0* first, const Elem_a6a7d0* last, Elem_a6a7d0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
