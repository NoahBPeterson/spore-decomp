// copy (0x00ae4590): assign each 0x64-byte element of [first, last) to dest (operator= 0xae4430); returns the end of the destination.
#include "game/types.h"

struct Elem_ae4590 {
    char mData[0x64];
    Elem_ae4590& operator=(const Elem_ae4590& o);   // 0x00ae4430
};

// @ 0x00ae4590
Elem_ae4590* Copy_ae4590(const Elem_ae4590* first, const Elem_ae4590* last, Elem_ae4590* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
