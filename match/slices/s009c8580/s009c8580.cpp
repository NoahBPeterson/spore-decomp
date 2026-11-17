// copy_backward (0x009c8580): assign the 0x468-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9b3490).
#include "game/types.h"

struct Elem_9c8580 {
    char mData[0x468];
    Elem_9c8580& operator=(const Elem_9c8580& o);   // 0x009b3490
};

// @ 0x009c8580
Elem_9c8580* CopyBackward_9c8580(const Elem_9c8580* first, const Elem_9c8580* last, Elem_9c8580* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
