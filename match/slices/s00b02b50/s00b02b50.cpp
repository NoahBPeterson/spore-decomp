// copy_backward (0x00b02b50): assign the 0x20-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xb01d30).
#include "game/types.h"

struct Elem_b02b50 {
    char mData[0x20];
    Elem_b02b50& operator=(const Elem_b02b50& o);   // 0x00b01d30
};

// @ 0x00b02b50
Elem_b02b50* CopyBackward_b02b50(const Elem_b02b50* first, const Elem_b02b50* last, Elem_b02b50* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
