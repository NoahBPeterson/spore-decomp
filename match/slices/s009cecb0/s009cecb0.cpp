// copy (0x009cecb0): assign each 0x108-byte element of [first, last) to dest (operator= 0x9ce790); returns the end of the destination.
#include "game/types.h"

struct Elem_9cecb0 {
    char mData[0x108];
    Elem_9cecb0& operator=(const Elem_9cecb0& o);   // 0x009ce790
};

// @ 0x009cecb0
Elem_9cecb0* Copy_9cecb0(const Elem_9cecb0* first, const Elem_9cecb0* last, Elem_9cecb0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
