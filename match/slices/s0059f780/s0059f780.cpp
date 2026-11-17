// copy_backward (0x0059f780): assign the 0xc4-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x59f0e0).
#include "game/types.h"

struct Elem_59f780 {
    char mData[0xc4];
    Elem_59f780& operator=(const Elem_59f780& o);   // 0x0059f0e0
};

// @ 0x0059f780
Elem_59f780* CopyBackward_59f780(const Elem_59f780* first, const Elem_59f780* last, Elem_59f780* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
