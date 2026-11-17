// copy (0x007cc670): assign each 0xac-byte element of [first, last) to dest (operator= 0x7cc5f0); returns the end of the destination.
#include "game/types.h"

struct Elem_7cc670 {
    char mData[0xac];
    Elem_7cc670& operator=(const Elem_7cc670& o);   // 0x007cc5f0
};

// @ 0x007cc670
Elem_7cc670* Copy_7cc670(const Elem_7cc670* first, const Elem_7cc670* last, Elem_7cc670* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
