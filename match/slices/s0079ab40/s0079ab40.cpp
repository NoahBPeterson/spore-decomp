// copy_backward (0x0079ab40): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7552e0).
#include "game/types.h"

struct Elem_79ab40 {
    char mData[0x14];
    Elem_79ab40& operator=(const Elem_79ab40& o);   // 0x007552e0
};

// @ 0x0079ab40
Elem_79ab40* CopyBackward_79ab40(const Elem_79ab40* first, const Elem_79ab40* last, Elem_79ab40* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
