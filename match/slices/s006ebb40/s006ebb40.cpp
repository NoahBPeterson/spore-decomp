// copy_backward (0x006ebb40): assign the 0x68-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x6eac80).
#include "game/types.h"

struct Elem_6ebb40 {
    char mData[0x68];
    Elem_6ebb40& operator=(const Elem_6ebb40& o);   // 0x006eac80
};

// @ 0x006ebb40
Elem_6ebb40* CopyBackward_6ebb40(const Elem_6ebb40* first, const Elem_6ebb40* last, Elem_6ebb40* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
