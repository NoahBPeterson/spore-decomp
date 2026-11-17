// copy (0x00dfe9a0): assign each 0x238-byte element of [first, last) to dest (operator= 0xdfe170); returns the end of the destination.
#include "game/types.h"

struct Elem_dfe9a0 {
    char mData[0x238];
    Elem_dfe9a0& operator=(const Elem_dfe9a0& o);   // 0x00dfe170
};

// @ 0x00dfe9a0
Elem_dfe9a0* Copy_dfe9a0(const Elem_dfe9a0* first, const Elem_dfe9a0* last, Elem_dfe9a0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
