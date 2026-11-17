// copy_backward (0x00bc4060): assign the 0x98-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xbc3f50).
#include "game/types.h"

struct Elem_bc4060 {
    char mData[0x98];
    Elem_bc4060& operator=(const Elem_bc4060& o);   // 0x00bc3f50
};

// @ 0x00bc4060
Elem_bc4060* CopyBackward_bc4060(const Elem_bc4060* first, const Elem_bc4060* last, Elem_bc4060* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
