// copy (0x00d5d530): assign each 0x64-byte element of [first, last) to dest (operator= 0xd5d4b0); returns the end of the destination.
#include "game/types.h"

struct Elem_d5d530 {
    char mData[0x64];
    Elem_d5d530& operator=(const Elem_d5d530& o);   // 0x00d5d4b0
};

// @ 0x00d5d530
Elem_d5d530* Copy_d5d530(const Elem_d5d530* first, const Elem_d5d530* last, Elem_d5d530* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
