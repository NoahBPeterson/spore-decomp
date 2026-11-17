// copy_backward (0x00dcec60): assign the 0x178-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdcea90).
#include "game/types.h"

struct Elem_dcec60 {
    char mData[0x178];
    Elem_dcec60& operator=(const Elem_dcec60& o);   // 0x00dcea90
};

// @ 0x00dcec60
Elem_dcec60* CopyBackward_dcec60(const Elem_dcec60* first, const Elem_dcec60* last, Elem_dcec60* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
