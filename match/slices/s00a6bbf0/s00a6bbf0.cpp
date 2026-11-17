// copy (0x00a6bbf0): assign each 0x58-byte element of [first, last) to dest (operator= 0xa6bb80); returns the end of the destination.
#include "game/types.h"

struct Elem_a6bbf0 {
    char mData[0x58];
    Elem_a6bbf0& operator=(const Elem_a6bbf0& o);   // 0x00a6bb80
};

// @ 0x00a6bbf0
Elem_a6bbf0* Copy_a6bbf0(const Elem_a6bbf0* first, const Elem_a6bbf0* last, Elem_a6bbf0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
