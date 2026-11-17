// copy_backward (0x0080caf0): assign the 0x42c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x80c9f0).
#include "game/types.h"

struct Elem_80caf0 {
    char mData[0x42c];
    Elem_80caf0& operator=(const Elem_80caf0& o);   // 0x0080c9f0
};

// @ 0x0080caf0
Elem_80caf0* CopyBackward_80caf0(const Elem_80caf0* first, const Elem_80caf0* last, Elem_80caf0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
