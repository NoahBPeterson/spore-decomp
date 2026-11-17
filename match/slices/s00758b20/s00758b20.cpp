// copy_backward (0x00758b20): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x50d4e0).
#include "game/types.h"

struct Elem_758b20 {
    char mData[0x14];
    Elem_758b20& operator=(const Elem_758b20& o);   // 0x0050d4e0
};

// @ 0x00758b20
Elem_758b20* CopyBackward_758b20(const Elem_758b20* first, const Elem_758b20* last, Elem_758b20* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
