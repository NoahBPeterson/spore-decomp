// copy_backward (0x00a874b0): assign the 0x58-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xa873c0).
#include "game/types.h"

struct Elem_a874b0 {
    char mData[0x58];
    Elem_a874b0& operator=(const Elem_a874b0& o);   // 0x00a873c0
};

// @ 0x00a874b0
Elem_a874b0* CopyBackward_a874b0(const Elem_a874b0* first, const Elem_a874b0* last, Elem_a874b0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
