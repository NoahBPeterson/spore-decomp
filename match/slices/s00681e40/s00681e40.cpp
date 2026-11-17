// copy_backward (0x00681e40): assign the 0xc4-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x681b50).
#include "game/types.h"

struct Elem_681e40 {
    char mData[0xc4];
    Elem_681e40& operator=(const Elem_681e40& o);   // 0x00681b50
};

// @ 0x00681e40
Elem_681e40* CopyBackward_681e40(const Elem_681e40* first, const Elem_681e40* last, Elem_681e40* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
