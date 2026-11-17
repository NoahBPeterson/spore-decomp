// copy_backward (0x00b0d210): assign the 0x8-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xb0d050).
#include "game/types.h"

struct Elem_b0d210 {
    char mData[0x8];
    Elem_b0d210& operator=(const Elem_b0d210& o);   // 0x00b0d050
};

// @ 0x00b0d210
Elem_b0d210* CopyBackward_b0d210(const Elem_b0d210* first, const Elem_b0d210* last, Elem_b0d210* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
