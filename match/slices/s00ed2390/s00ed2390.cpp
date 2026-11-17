// copy (0x00ed2390): assign each 0x14-byte element of [first, last) to dest (operator= 0xed2260); returns the end of the destination.
#include "game/types.h"

struct Elem_ed2390 {
    char mData[0x14];
    Elem_ed2390& operator=(const Elem_ed2390& o);   // 0x00ed2260
};

// @ 0x00ed2390
Elem_ed2390* Copy_ed2390(const Elem_ed2390* first, const Elem_ed2390* last, Elem_ed2390* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
