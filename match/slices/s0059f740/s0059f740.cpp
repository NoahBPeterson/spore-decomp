// copy (0x0059f740): assign each 0xc4-byte element of [first, last) to dest (operator= 0x59f0e0); returns the end of the destination.
#include "game/types.h"

struct Elem_59f740 {
    char mData[0xc4];
    Elem_59f740& operator=(const Elem_59f740& o);   // 0x0059f0e0
};

// @ 0x0059f740
Elem_59f740* Copy_59f740(const Elem_59f740* first, const Elem_59f740* last, Elem_59f740* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
