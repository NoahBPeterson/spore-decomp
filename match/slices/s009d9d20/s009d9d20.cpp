// copy_backward (0x009d9d20): assign the 0x104-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9d9620).
#include "game/types.h"

struct Elem_9d9d20 {
    char mData[0x104];
    Elem_9d9d20& operator=(const Elem_9d9d20& o);   // 0x009d9620
};

// @ 0x009d9d20
Elem_9d9d20* CopyBackward_9d9d20(const Elem_9d9d20* first, const Elem_9d9d20* last, Elem_9d9d20* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
