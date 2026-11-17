// copy (0x00717a90): assign each 0xd0-byte element of [first, last) to dest (operator= 0x7179e0); returns the end of the destination.
#include "game/types.h"

struct Elem_717a90 {
    char mData[0xd0];
    Elem_717a90& operator=(const Elem_717a90& o);   // 0x007179e0
};

// @ 0x00717a90
Elem_717a90* Copy_717a90(const Elem_717a90* first, const Elem_717a90* last, Elem_717a90* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
