// copy (0x00758ae0): assign each 0x14-byte element of [first, last) to dest (operator= 0x50d4e0); returns the end of the destination.
#include "game/types.h"

struct Elem_758ae0 {
    char mData[0x14];
    Elem_758ae0& operator=(const Elem_758ae0& o);   // 0x0050d4e0
};

// @ 0x00758ae0
Elem_758ae0* Copy_758ae0(const Elem_758ae0* first, const Elem_758ae0* last, Elem_758ae0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
