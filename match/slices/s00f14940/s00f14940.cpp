// copy_backward (0x00f14940): assign the 0x70-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xf147e0).
#include "game/types.h"

struct Elem_f14940 {
    char mData[0x70];
    Elem_f14940& operator=(const Elem_f14940& o);   // 0x00f147e0
};

// @ 0x00f14940
Elem_f14940* CopyBackward_f14940(const Elem_f14940* first, const Elem_f14940* last, Elem_f14940* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
