// copy_backward (0x0079f770): assign the 0x14-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x79f640).
#include "game/types.h"

struct Elem_79f770 {
    char mData[0x14];
    Elem_79f770& operator=(const Elem_79f770& o);   // 0x0079f640
};

// @ 0x0079f770
Elem_79f770* CopyBackward_79f770(const Elem_79f770* first, const Elem_79f770* last, Elem_79f770* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
