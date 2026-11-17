// copy_backward (0x00b85980): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x473500).
#include "game/types.h"

struct Elem_b85980 {
    char mData[0x14];
    Elem_b85980& operator=(const Elem_b85980& o);   // 0x00473500
};

// @ 0x00b85980
Elem_b85980* CopyBackward_b85980(const Elem_b85980* first, const Elem_b85980* last, Elem_b85980* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
