// copy_backward (0x00708f00): assign the 0x144-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7089a0).
#include "game/types.h"

struct Elem_708f00 {
    char mData[0x144];
    Elem_708f00& operator=(const Elem_708f00& o);   // 0x007089a0
};

// @ 0x00708f00
Elem_708f00* CopyBackward_708f00(const Elem_708f00* first, const Elem_708f00* last, Elem_708f00* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
