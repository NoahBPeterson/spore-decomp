// copy_backward (0x00f2e330): assign the 0x534-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdfedb0).
#include "game/types.h"

struct Elem_f2e330 {
    char mData[0x534];
    Elem_f2e330& operator=(const Elem_f2e330& o);   // 0x00dfedb0
};

// @ 0x00f2e330
Elem_f2e330* CopyBackward_f2e330(const Elem_f2e330* first, const Elem_f2e330* last, Elem_f2e330* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
