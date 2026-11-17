// copy (0x00c0ff80): assign each 0x24-byte element of [first, last) to dest (operator= 0xc0fe30); returns the end of the destination.
#include "game/types.h"

struct Elem_c0ff80 {
    char mData[0x24];
    Elem_c0ff80& operator=(const Elem_c0ff80& o);   // 0x00c0fe30
};

// @ 0x00c0ff80
Elem_c0ff80* Copy_c0ff80(const Elem_c0ff80* first, const Elem_c0ff80* last, Elem_c0ff80* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
