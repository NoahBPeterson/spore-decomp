// copy (0x0080cab0): assign each 0x42c-byte element of [first, last) to dest (operator= 0x80c9f0); returns the end of the destination.
#include "game/types.h"

struct Elem_80cab0 {
    char mData[0x42c];
    Elem_80cab0& operator=(const Elem_80cab0& o);   // 0x0080c9f0
};

// @ 0x0080cab0
Elem_80cab0* Copy_80cab0(const Elem_80cab0* first, const Elem_80cab0* last, Elem_80cab0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
