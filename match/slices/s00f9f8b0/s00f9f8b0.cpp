// copy_backward (0x00f9f8b0): assign the 0xac-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xf9f620).
#include "game/types.h"

struct Elem_f9f8b0 {
    char mData[0xac];
    Elem_f9f8b0& operator=(const Elem_f9f8b0& o);   // 0x00f9f620
};

// @ 0x00f9f8b0
Elem_f9f8b0* CopyBackward_f9f8b0(const Elem_f9f8b0* first, const Elem_f9f8b0* last, Elem_f9f8b0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
