// copy_backward (0x006ebb00): assign the 0x70-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x6eabc0).
#include "game/types.h"

struct Elem_6ebb00 {
    char mData[0x70];
    Elem_6ebb00& operator=(const Elem_6ebb00& o);   // 0x006eabc0
};

// @ 0x006ebb00
Elem_6ebb00* CopyBackward_6ebb00(const Elem_6ebb00* first, const Elem_6ebb00* last, Elem_6ebb00* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
