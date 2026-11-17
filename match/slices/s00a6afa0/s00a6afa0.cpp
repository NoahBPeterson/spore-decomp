// copy (0x00a6afa0): assign each 0x84-byte element of [first, last) to dest (operator= 0xa6ac70); returns the end of the destination.
#include "game/types.h"

struct Elem_a6afa0 {
    char mData[0x84];
    Elem_a6afa0& operator=(const Elem_a6afa0& o);   // 0x00a6ac70
};

// @ 0x00a6afa0
Elem_a6afa0* Copy_a6afa0(const Elem_a6afa0* first, const Elem_a6afa0* last, Elem_a6afa0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
