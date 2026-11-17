// copy_backward (0x009dc340): assign the 0x44-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9dbfd0).
#include "game/types.h"

struct Elem_9dc340 {
    char mData[0x44];
    Elem_9dc340& operator=(const Elem_9dc340& o);   // 0x009dbfd0
};

// @ 0x009dc340
Elem_9dc340* CopyBackward_9dc340(const Elem_9dc340* first, const Elem_9dc340* last, Elem_9dc340* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
