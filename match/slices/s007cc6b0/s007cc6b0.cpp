// copy_backward (0x007cc6b0): assign the 0xac-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7cc5f0).
#include "game/types.h"

struct Elem_7cc6b0 {
    char mData[0xac];
    Elem_7cc6b0& operator=(const Elem_7cc6b0& o);   // 0x007cc5f0
};

// @ 0x007cc6b0
Elem_7cc6b0* CopyBackward_7cc6b0(const Elem_7cc6b0* first, const Elem_7cc6b0* last, Elem_7cc6b0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
