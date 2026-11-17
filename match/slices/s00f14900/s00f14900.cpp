// copy (0x00f14900): assign each 0x70-byte element of [first, last) to dest (operator= 0xf147e0); returns the end of the destination.
#include "game/types.h"

struct Elem_f14900 {
    char mData[0x70];
    Elem_f14900& operator=(const Elem_f14900& o);   // 0x00f147e0
};

// @ 0x00f14900
Elem_f14900* Copy_f14900(const Elem_f14900* first, const Elem_f14900* last, Elem_f14900* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
