// copy_backward (0x00da5620): assign the 0x210-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xda5550).
#include "game/types.h"

struct Elem_da5620 {
    char mData[0x210];
    Elem_da5620& operator=(const Elem_da5620& o);   // 0x00da5550
};

// @ 0x00da5620
Elem_da5620* CopyBackward_da5620(const Elem_da5620* first, const Elem_da5620* last, Elem_da5620* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
