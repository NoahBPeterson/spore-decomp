// copy_backward (0x006ed890): assign the 0xc0-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x6ecfc0).
#include "game/types.h"

struct Elem_6ed890 {
    char mData[0xc0];
    Elem_6ed890& operator=(const Elem_6ed890& o);   // 0x006ecfc0
};

// @ 0x006ed890
Elem_6ed890* CopyBackward_6ed890(const Elem_6ed890* first, const Elem_6ed890* last, Elem_6ed890* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
