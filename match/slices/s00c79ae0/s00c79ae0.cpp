// copy (0x00c79ae0): assign each 0x14-byte element of [first, last) to dest (operator= 0xdb5b30); returns the end of the destination.
#include "game/types.h"

struct Elem_c79ae0 {
    char mData[0x14];
    Elem_c79ae0& operator=(const Elem_c79ae0& o);   // 0x00db5b30
};

// @ 0x00c79ae0
Elem_c79ae0* Copy_c79ae0(const Elem_c79ae0* first, const Elem_c79ae0* last, Elem_c79ae0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
