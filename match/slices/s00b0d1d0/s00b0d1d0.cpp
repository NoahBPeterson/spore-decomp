// copy (0x00b0d1d0): assign each 0x8-byte element of [first, last) to dest (operator= 0xb0d050); returns the end of the destination.
#include "game/types.h"

struct Elem_b0d1d0 {
    char mData[0x8];
    Elem_b0d1d0& operator=(const Elem_b0d1d0& o);   // 0x00b0d050
};

// @ 0x00b0d1d0
Elem_b0d1d0* Copy_b0d1d0(const Elem_b0d1d0* first, const Elem_b0d1d0* last, Elem_b0d1d0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
