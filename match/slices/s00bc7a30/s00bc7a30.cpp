// copy_backward (0x00bc7a30): assign the 0x3c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xbc7920).
#include "game/types.h"

struct Elem_bc7a30 {
    char mData[0x3c];
    Elem_bc7a30& operator=(const Elem_bc7a30& o);   // 0x00bc7920
};

// @ 0x00bc7a30
Elem_bc7a30* CopyBackward_bc7a30(const Elem_bc7a30* first, const Elem_bc7a30* last, Elem_bc7a30* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
