// copy_backward (0x00a6eab0): assign the 0x84-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xa6ac70).
#include "game/types.h"

struct Elem_a6eab0 {
    char mData[0x84];
    Elem_a6eab0& operator=(const Elem_a6eab0& o);   // 0x00a6ac70
};

// @ 0x00a6eab0
Elem_a6eab0* CopyBackward_a6eab0(const Elem_a6eab0* first, const Elem_a6eab0* last, Elem_a6eab0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
