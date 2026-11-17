// copy_backward (0x00aed470): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x6b5430).
#include "game/types.h"

struct Elem_aed470 {
    char mData[0x14];
    Elem_aed470& operator=(const Elem_aed470& o);   // 0x006b5430
};

// @ 0x00aed470
Elem_aed470* CopyBackward_aed470(const Elem_aed470* first, const Elem_aed470* last, Elem_aed470* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
