// copy (0x009bf5c0): assign each 0x2bc-byte element of [first, last) to dest (operator= 0x9bf210); returns the end of the destination.
#include "game/types.h"

struct Elem_9bf5c0 {
    char mData[0x2bc];
    Elem_9bf5c0& operator=(const Elem_9bf5c0& o);   // 0x009bf210
};

// @ 0x009bf5c0
Elem_9bf5c0* Copy_9bf5c0(const Elem_9bf5c0* first, const Elem_9bf5c0* last, Elem_9bf5c0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
