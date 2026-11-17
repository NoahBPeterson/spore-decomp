// copy (0x009a1c20): assign each 0x1f0-byte element of [first, last) to dest (operator= 0x9a18a0); returns the end of the destination.
#include "game/types.h"

struct Elem_9a1c20 {
    char mData[0x1f0];
    Elem_9a1c20& operator=(const Elem_9a1c20& o);   // 0x009a18a0
};

// @ 0x009a1c20
Elem_9a1c20* Copy_9a1c20(const Elem_9a1c20* first, const Elem_9a1c20* last, Elem_9a1c20* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
