// copy_backward (0x0079b470): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x79b360).
#include "game/types.h"

struct Elem_79b470 {
    char mData[0x14];
    Elem_79b470& operator=(const Elem_79b470& o);   // 0x0079b360
};

// @ 0x0079b470
Elem_79b470* CopyBackward_79b470(const Elem_79b470* first, const Elem_79b470* last, Elem_79b470* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
