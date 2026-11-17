// copy_backward (0x00bc65b0): assign the 0x7b4-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xbc6360).
#include "game/types.h"

struct Elem_bc65b0 {
    char mData[0x7b4];
    Elem_bc65b0& operator=(const Elem_bc65b0& o);   // 0x00bc6360
};

// @ 0x00bc65b0
Elem_bc65b0* CopyBackward_bc65b0(const Elem_bc65b0* first, const Elem_bc65b0* last, Elem_bc65b0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
