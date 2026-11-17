// copy_backward (0x009dc380): assign the 0x58-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9dc050).
#include "game/types.h"

struct Elem_9dc380 {
    char mData[0x58];
    Elem_9dc380& operator=(const Elem_9dc380& o);   // 0x009dc050
};

// @ 0x009dc380
Elem_9dc380* CopyBackward_9dc380(const Elem_9dc380* first, const Elem_9dc380* last, Elem_9dc380* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
