// copy (0x009bf540): assign each 0x10c-byte element of [first, last) to dest (operator= 0x9befa0); returns the end of the destination.
#include "game/types.h"

struct Elem_9bf540 {
    char mData[0x10c];
    Elem_9bf540& operator=(const Elem_9bf540& o);   // 0x009befa0
};

// @ 0x009bf540
Elem_9bf540* Copy_9bf540(const Elem_9bf540* first, const Elem_9bf540* last, Elem_9bf540* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
