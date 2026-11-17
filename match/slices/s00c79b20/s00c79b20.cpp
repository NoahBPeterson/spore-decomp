// copy_backward (0x00c79b20): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdb5b30).
#include "game/types.h"

struct Elem_c79b20 {
    char mData[0x14];
    Elem_c79b20& operator=(const Elem_c79b20& o);   // 0x00db5b30
};

// @ 0x00c79b20
Elem_c79b20* CopyBackward_c79b20(const Elem_c79b20* first, const Elem_c79b20* last, Elem_c79b20* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
