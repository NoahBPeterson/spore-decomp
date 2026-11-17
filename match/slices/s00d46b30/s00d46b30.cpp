// copy_backward (0x00d46b30): assign the 0x2c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xd46970).
#include "game/types.h"

struct Elem_d46b30 {
    char mData[0x2c];
    Elem_d46b30& operator=(const Elem_d46b30& o);   // 0x00d46970
};

// @ 0x00d46b30
Elem_d46b30* CopyBackward_d46b30(const Elem_d46b30* first, const Elem_d46b30* last, Elem_d46b30* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
