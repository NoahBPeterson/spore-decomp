// copy_backward (0x0104f1b0): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x6609a0).
#include "game/types.h"

struct Elem_104f1b0 {
    char mData[0x14];
    Elem_104f1b0& operator=(const Elem_104f1b0& o);   // 0x006609a0
};

// @ 0x0104f1b0
Elem_104f1b0* CopyBackward_104f1b0(const Elem_104f1b0* first, const Elem_104f1b0* last, Elem_104f1b0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
