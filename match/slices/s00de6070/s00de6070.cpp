// copy (0x00de6070): assign each 0xbc-byte element of [first, last) to dest (operator= 0xb26fb0); returns the end of the destination.
#include "game/types.h"

struct Elem_de6070 {
    char mData[0xbc];
    Elem_de6070& operator=(const Elem_de6070& o);   // 0x00b26fb0
};

// @ 0x00de6070
Elem_de6070* Copy_de6070(const Elem_de6070* first, const Elem_de6070* last, Elem_de6070* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
