// copy_backward (0x006ebf10): assign the 0x70-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x6ebb80).
#include "game/types.h"

struct Elem_6ebf10 {
    char mData[0x70];
    Elem_6ebf10& operator=(const Elem_6ebf10& o);   // 0x006ebb80
};

// @ 0x006ebf10
Elem_6ebf10* CopyBackward_6ebf10(const Elem_6ebf10* first, const Elem_6ebf10* last, Elem_6ebf10* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
