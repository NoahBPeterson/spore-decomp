// copy_backward (0x00745f40): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7456a0).
#include "game/types.h"

struct Elem_745f40 {
    char mData[0x14];
    Elem_745f40& operator=(const Elem_745f40& o);   // 0x007456a0
};

// @ 0x00745f40
Elem_745f40* CopyBackward_745f40(const Elem_745f40* first, const Elem_745f40* last, Elem_745f40* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
