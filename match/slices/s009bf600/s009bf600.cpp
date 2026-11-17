// copy_backward (0x009bf600): assign the 0x10c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9befa0).
#include "game/types.h"

struct Elem_9bf600 {
    char mData[0x10c];
    Elem_9bf600& operator=(const Elem_9bf600& o);   // 0x009befa0
};

// @ 0x009bf600
Elem_9bf600* CopyBackward_9bf600(const Elem_9bf600* first, const Elem_9bf600* last, Elem_9bf600* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
