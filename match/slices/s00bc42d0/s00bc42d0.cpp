// copy (0x00bc42d0): assign each 0x98-byte element of [first, last) to dest (operator= 0xbc3f50); returns the end of the destination.
#include "game/types.h"

struct Elem_bc42d0 {
    char mData[0x98];
    Elem_bc42d0& operator=(const Elem_bc42d0& o);   // 0x00bc3f50
};

// @ 0x00bc42d0
Elem_bc42d0* Copy_bc42d0(const Elem_bc42d0* first, const Elem_bc42d0* last, Elem_bc42d0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
