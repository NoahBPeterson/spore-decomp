// copy (0x00a6a5d0): assign each 0x14-byte element of [first, last) to dest (operator= 0xa69e50); returns the end of the destination.
#include "game/types.h"

struct Elem_a6a5d0 {
    char mData[0x14];
    Elem_a6a5d0& operator=(const Elem_a6a5d0& o);   // 0x00a69e50
};

// @ 0x00a6a5d0
Elem_a6a5d0* Copy_a6a5d0(const Elem_a6a5d0* first, const Elem_a6a5d0* last, Elem_a6a5d0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
