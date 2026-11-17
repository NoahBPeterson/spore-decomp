// copy_backward (0x00ae45d0): assign the 0x64-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xae4430).
#include "game/types.h"

struct Elem_ae45d0 {
    char mData[0x64];
    Elem_ae45d0& operator=(const Elem_ae45d0& o);   // 0x00ae4430
};

// @ 0x00ae45d0
Elem_ae45d0* CopyBackward_ae45d0(const Elem_ae45d0* first, const Elem_ae45d0* last, Elem_ae45d0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
