// copy_backward (0x00ed23d0): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xed2260).
#include "game/types.h"

struct Elem_ed23d0 {
    char mData[0x14];
    Elem_ed23d0& operator=(const Elem_ed23d0& o);   // 0x00ed2260
};

// @ 0x00ed23d0
Elem_ed23d0* CopyBackward_ed23d0(const Elem_ed23d0* first, const Elem_ed23d0* last, Elem_ed23d0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
