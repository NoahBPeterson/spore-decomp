// copy_backward (0x00717b30): assign the 0xd0-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7179e0).
#include "game/types.h"

struct Elem_717b30 {
    char mData[0xd0];
    Elem_717b30& operator=(const Elem_717b30& o);   // 0x007179e0
};

// @ 0x00717b30
Elem_717b30* CopyBackward_717b30(const Elem_717b30* first, const Elem_717b30* last, Elem_717b30* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
