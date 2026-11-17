// copy_backward (0x00d5d570): assign the 0x64-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xd5d4b0).
#include "game/types.h"

struct Elem_d5d570 {
    char mData[0x64];
    Elem_d5d570& operator=(const Elem_d5d570& o);   // 0x00d5d4b0
};

// @ 0x00d5d570
Elem_d5d570* CopyBackward_d5d570(const Elem_d5d570* first, const Elem_d5d570* last, Elem_d5d570* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
