// copy (0x00b969a0): assign each 0x14-byte element of [first, last) to dest (operator= 0x473500); returns the end of the destination.
#include "game/types.h"

struct Elem_b969a0 {
    char mData[0x14];
    Elem_b969a0& operator=(const Elem_b969a0& o);   // 0x00473500
};

// @ 0x00b969a0
Elem_b969a0* Copy_b969a0(const Elem_b969a0* first, const Elem_b969a0* last, Elem_b969a0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
