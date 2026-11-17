// copy_backward (0x00f2cf60): assign the 0x4e0-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdfcce0).
#include "game/types.h"

struct Elem_f2cf60 {
    char mData[0x4e0];
    Elem_f2cf60& operator=(const Elem_f2cf60& o);   // 0x00dfcce0
};

// @ 0x00f2cf60
Elem_f2cf60* CopyBackward_f2cf60(const Elem_f2cf60* first, const Elem_f2cf60* last, Elem_f2cf60* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
