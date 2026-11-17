// copy (0x00708ec0): assign each 0x144-byte element of [first, last) to dest (operator= 0x7089a0); returns the end of the destination.
#include "game/types.h"

struct Elem_708ec0 {
    char mData[0x144];
    Elem_708ec0& operator=(const Elem_708ec0& o);   // 0x007089a0
};

// @ 0x00708ec0
Elem_708ec0* Copy_708ec0(const Elem_708ec0* first, const Elem_708ec0* last, Elem_708ec0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
