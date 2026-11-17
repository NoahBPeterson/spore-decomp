// copy_backward (0x01023460): assign the 0x1c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7d0b80).
#include "game/types.h"

struct Elem_1023460 {
    char mData[0x1c];
    Elem_1023460& operator=(const Elem_1023460& o);   // 0x007d0b80
};

// @ 0x01023460
Elem_1023460* CopyBackward_1023460(const Elem_1023460* first, const Elem_1023460* last, Elem_1023460* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
