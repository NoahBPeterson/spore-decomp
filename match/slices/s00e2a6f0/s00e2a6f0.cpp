// copy (0x00e2a6f0): assign each 0x14-byte element of [first, last) to dest (operator= 0x6b5430); returns the end of the destination.
#include "game/types.h"

struct Elem_e2a6f0 {
    char mData[0x14];
    Elem_e2a6f0& operator=(const Elem_e2a6f0& o);   // 0x006b5430
};

// @ 0x00e2a6f0
Elem_e2a6f0* Copy_e2a6f0(const Elem_e2a6f0* first, const Elem_e2a6f0* last, Elem_e2a6f0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
