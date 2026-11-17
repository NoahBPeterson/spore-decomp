// copy_backward (0x00757fb0): assign the 0x7c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x429370).
#include "game/types.h"

struct Elem_757fb0 {
    char mData[0x7c];
    Elem_757fb0& operator=(const Elem_757fb0& o);   // 0x00429370
};

// @ 0x00757fb0
Elem_757fb0* CopyBackward_757fb0(const Elem_757fb0* first, const Elem_757fb0* last, Elem_757fb0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
