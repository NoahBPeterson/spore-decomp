// copy_backward (0x00723cb0): assign the 0x68-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x723a70).
#include "game/types.h"

struct Elem_723cb0 {
    char mData[0x68];
    Elem_723cb0& operator=(const Elem_723cb0& o);   // 0x00723a70
};

// @ 0x00723cb0
Elem_723cb0* CopyBackward_723cb0(const Elem_723cb0* first, const Elem_723cb0* last, Elem_723cb0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
