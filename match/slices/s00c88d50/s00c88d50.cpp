// copy_backward (0x00c88d50): assign the 0x3c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xc88c30).
#include "game/types.h"

struct Elem_c88d50 {
    char mData[0x3c];
    Elem_c88d50& operator=(const Elem_c88d50& o);   // 0x00c88c30
};

// @ 0x00c88d50
Elem_c88d50* CopyBackward_c88d50(const Elem_c88d50* first, const Elem_c88d50* last, Elem_c88d50* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
