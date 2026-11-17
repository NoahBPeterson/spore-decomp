// copy_backward (0x00ebbe30): assign the 0x50-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xebbc10).
#include "game/types.h"

struct Elem_ebbe30 {
    char mData[0x50];
    Elem_ebbe30& operator=(const Elem_ebbe30& o);   // 0x00ebbc10
};

// @ 0x00ebbe30
Elem_ebbe30* CopyBackward_ebbe30(const Elem_ebbe30* first, const Elem_ebbe30* last, Elem_ebbe30* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
