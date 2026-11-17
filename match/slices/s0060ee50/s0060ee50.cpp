// copy (0x0060ee50): assign each 0x70-byte element of [first, last) to dest (operator= 0x5496a0); returns the end of the destination.
#include "game/types.h"

struct Elem_60ee50 {
    char mData[0x70];
    Elem_60ee50& operator=(const Elem_60ee50& o);   // 0x005496a0
};

// @ 0x0060ee50
Elem_60ee50* Copy_60ee50(const Elem_60ee50* first, const Elem_60ee50* last, Elem_60ee50* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
