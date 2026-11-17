// copy_backward (0x00f33a80): assign the 0x38-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x537dc0).
#include "game/types.h"

struct Elem_f33a80 {
    char mData[0x38];
    Elem_f33a80& operator=(const Elem_f33a80& o);   // 0x00537dc0
};

// @ 0x00f33a80
Elem_f33a80* CopyBackward_f33a80(const Elem_f33a80* first, const Elem_f33a80* last, Elem_f33a80* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
