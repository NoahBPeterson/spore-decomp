// copy_backward (0x009a1a20): assign the 0x1f0-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9a18a0).
#include "game/types.h"

struct Elem_9a1a20 {
    char mData[0x1f0];
    Elem_9a1a20& operator=(const Elem_9a1a20& o);   // 0x009a18a0
};

// @ 0x009a1a20
Elem_9a1a20* CopyBackward_9a1a20(const Elem_9a1a20* first, const Elem_9a1a20* last, Elem_9a1a20* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
