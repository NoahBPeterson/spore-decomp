// copy_backward (0x00f2d640): assign the 0x238-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdfe170).
#include "game/types.h"

struct Elem_f2d640 {
    char mData[0x238];
    Elem_f2d640& operator=(const Elem_f2d640& o);   // 0x00dfe170
};

// @ 0x00f2d640
Elem_f2d640* CopyBackward_f2d640(const Elem_f2d640* first, const Elem_f2d640* last, Elem_f2d640* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
