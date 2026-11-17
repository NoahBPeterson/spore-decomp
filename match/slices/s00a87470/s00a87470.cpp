// copy (0x00a87470): assign each 0x58-byte element of [first, last) to dest (operator= 0xa873c0); returns the end of the destination.
#include "game/types.h"

struct Elem_a87470 {
    char mData[0x58];
    Elem_a87470& operator=(const Elem_a87470& o);   // 0x00a873c0
};

// @ 0x00a87470
Elem_a87470* Copy_a87470(const Elem_a87470* first, const Elem_a87470* last, Elem_a87470* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
