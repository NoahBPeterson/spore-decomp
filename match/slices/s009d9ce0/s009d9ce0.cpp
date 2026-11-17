// copy (0x009d9ce0): assign each 0x104-byte element of [first, last) to dest (operator= 0x9d9620); returns the end of the destination.
#include "game/types.h"

struct Elem_9d9ce0 {
    char mData[0x104];
    Elem_9d9ce0& operator=(const Elem_9d9ce0& o);   // 0x009d9620
};

// @ 0x009d9ce0
Elem_9d9ce0* Copy_9d9ce0(const Elem_9d9ce0* first, const Elem_9d9ce0* last, Elem_9d9ce0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
