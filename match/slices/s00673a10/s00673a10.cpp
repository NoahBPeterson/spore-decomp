// copy (0x00673a10): assign each 0x63c-byte element of [first, last) to dest (operator= 0x673940); returns the end of the destination.
#include "game/types.h"

struct Elem_673a10 {
    char mData[0x63c];
    Elem_673a10& operator=(const Elem_673a10& o);   // 0x00673940
};

// @ 0x00673a10
Elem_673a10* Copy_673a10(const Elem_673a10* first, const Elem_673a10* last, Elem_673a10* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
