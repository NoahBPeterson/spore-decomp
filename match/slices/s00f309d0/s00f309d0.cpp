// copy (0x00f309d0): assign each 0x84-byte element of [first, last) to dest (operator= 0xf30910); returns the end of the destination.
#include "game/types.h"

struct Elem_f309d0 {
    char mData[0x84];
    Elem_f309d0& operator=(const Elem_f309d0& o);   // 0x00f30910
};

// @ 0x00f309d0
Elem_f309d0* Copy_f309d0(const Elem_f309d0* first, const Elem_f309d0* last, Elem_f309d0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
