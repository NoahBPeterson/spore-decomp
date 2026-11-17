// copy (0x00bc79f0): assign each 0x3c-byte element of [first, last) to dest (operator= 0xbc7920); returns the end of the destination.
#include "game/types.h"

struct Elem_bc79f0 {
    char mData[0x3c];
    Elem_bc79f0& operator=(const Elem_bc79f0& o);   // 0x00bc7920
};

// @ 0x00bc79f0
Elem_bc79f0* Copy_bc79f0(const Elem_bc79f0* first, const Elem_bc79f0* last, Elem_bc79f0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
