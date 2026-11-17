// copy_backward (0x00f2e790): assign the 0x27e0-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdfee80).
#include "game/types.h"

struct Elem_f2e790 {
    char mData[0x27e0];
    Elem_f2e790& operator=(const Elem_f2e790& o);   // 0x00dfee80
};

// @ 0x00f2e790
Elem_f2e790* CopyBackward_f2e790(const Elem_f2e790* first, const Elem_f2e790* last, Elem_f2e790* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
