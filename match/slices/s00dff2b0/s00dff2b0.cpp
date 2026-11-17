// copy (0x00dff2b0): assign each 0x27e0-byte element of [first, last) to dest (operator= 0xdfee80); returns the end of the destination.
#include "game/types.h"

struct Elem_dff2b0 {
    char mData[0x27e0];
    Elem_dff2b0& operator=(const Elem_dff2b0& o);   // 0x00dfee80
};

// @ 0x00dff2b0
Elem_dff2b0* Copy_dff2b0(const Elem_dff2b0* first, const Elem_dff2b0* last, Elem_dff2b0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
