// copy (0x00dcec20): assign each 0x178-byte element of [first, last) to dest (operator= 0xdcea90); returns the end of the destination.
#include "game/types.h"

struct Elem_dcec20 {
    char mData[0x178];
    Elem_dcec20& operator=(const Elem_dcec20& o);   // 0x00dcea90
};

// @ 0x00dcec20
Elem_dcec20* Copy_dcec20(const Elem_dcec20* first, const Elem_dcec20* last, Elem_dcec20* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
