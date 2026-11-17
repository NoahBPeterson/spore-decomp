// copy (0x00b027f0): assign each 0x20-byte element of [first, last) to dest (operator= 0xb01d30); returns the end of the destination.
#include "game/types.h"

struct Elem_b027f0 {
    char mData[0x20];
    Elem_b027f0& operator=(const Elem_b027f0& o);   // 0x00b01d30
};

// @ 0x00b027f0
Elem_b027f0* Copy_b027f0(const Elem_b027f0* first, const Elem_b027f0* last, Elem_b027f0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
