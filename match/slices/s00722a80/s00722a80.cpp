// copy (0x00722a80): assign each 0x64-byte element of [first, last) to dest (operator= 0x7229f0); returns the end of the destination.
#include "game/types.h"

struct Elem_722a80 {
    char mData[0x64];
    Elem_722a80& operator=(const Elem_722a80& o);   // 0x007229f0
};

// @ 0x00722a80
Elem_722a80* Copy_722a80(const Elem_722a80* first, const Elem_722a80* last, Elem_722a80* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
