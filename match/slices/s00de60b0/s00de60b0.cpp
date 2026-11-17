// copy_backward (0x00de60b0): assign the 0xbc-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xb26fb0).
#include "game/types.h"

struct Elem_de60b0 {
    char mData[0xbc];
    Elem_de60b0& operator=(const Elem_de60b0& o);   // 0x00b26fb0
};

// @ 0x00de60b0
Elem_de60b0* CopyBackward_de60b0(const Elem_de60b0* first, const Elem_de60b0* last, Elem_de60b0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
