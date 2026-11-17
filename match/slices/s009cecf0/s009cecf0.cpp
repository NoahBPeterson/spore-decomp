// copy_backward (0x009cecf0): assign the 0x108-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9ce790).
#include "game/types.h"

struct Elem_9cecf0 {
    char mData[0x108];
    Elem_9cecf0& operator=(const Elem_9cecf0& o);   // 0x009ce790
};

// @ 0x009cecf0
Elem_9cecf0* CopyBackward_9cecf0(const Elem_9cecf0* first, const Elem_9cecf0* last, Elem_9cecf0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
