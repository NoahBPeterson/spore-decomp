// copy_backward (0x0059ee20): assign the 0x18-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x810050).
#include "game/types.h"

struct Elem_59ee20 {
    char mData[0x18];
    Elem_59ee20& operator=(const Elem_59ee20& o);   // 0x00810050
};

// @ 0x0059ee20
Elem_59ee20* CopyBackward_59ee20(const Elem_59ee20* first, const Elem_59ee20* last, Elem_59ee20* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
