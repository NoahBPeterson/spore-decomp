// copy_backward (0x00d66210): assign the 0x18-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xd66120).
#include "game/types.h"

struct Elem_d66210 {
    char mData[0x18];
    Elem_d66210& operator=(const Elem_d66210& o);   // 0x00d66120
};

// @ 0x00d66210
Elem_d66210* CopyBackward_d66210(const Elem_d66210* first, const Elem_d66210* last, Elem_d66210* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
