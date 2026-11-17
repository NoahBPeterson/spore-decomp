// copy (0x00c88d10): assign each 0x3c-byte element of [first, last) to dest (operator= 0xc88c30); returns the end of the destination.
#include "game/types.h"

struct Elem_c88d10 {
    char mData[0x3c];
    Elem_c88d10& operator=(const Elem_c88d10& o);   // 0x00c88c30
};

// @ 0x00c88d10
Elem_c88d10* Copy_c88d10(const Elem_c88d10* first, const Elem_c88d10* last, Elem_c88d10* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
