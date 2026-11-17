// copy_backward (0x00763f90): assign the 0xa0-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x700290).
#include "game/types.h"

struct Elem_763f90 {
    char mData[0xa0];
    Elem_763f90& operator=(const Elem_763f90& o);   // 0x00700290
};

// @ 0x00763f90
Elem_763f90* CopyBackward_763f90(const Elem_763f90* first, const Elem_763f90* last, Elem_763f90* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
