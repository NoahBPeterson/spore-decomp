// copy_backward (0x0064f950): assign the 0x20-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x64f450).
#include "game/types.h"

struct Elem_64f950 {
    char mData[0x20];
    Elem_64f950& operator=(const Elem_64f950& o);   // 0x0064f450
};

// @ 0x0064f950
Elem_64f950* CopyBackward_64f950(const Elem_64f950* first, const Elem_64f950* last, Elem_64f950* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
