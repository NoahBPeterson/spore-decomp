// copy_backward (0x00601d40): assign the 0x58-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x601c50).
#include "game/types.h"

struct Elem_601d40 {
    char mData[0x58];
    Elem_601d40& operator=(const Elem_601d40& o);   // 0x00601c50
};

// @ 0x00601d40
Elem_601d40* CopyBackward_601d40(const Elem_601d40* first, const Elem_601d40* last, Elem_601d40* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
