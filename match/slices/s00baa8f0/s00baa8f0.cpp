// copy_backward (0x00baa8f0): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x1011cc0).
#include "game/types.h"

struct Elem_baa8f0 {
    char mData[0x14];
    Elem_baa8f0& operator=(const Elem_baa8f0& o);   // 0x01011cc0
};

// @ 0x00baa8f0
Elem_baa8f0* CopyBackward_baa8f0(const Elem_baa8f0* first, const Elem_baa8f0* last, Elem_baa8f0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
