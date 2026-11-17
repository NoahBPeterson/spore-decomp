// copy (0x009b4310): assign each 0x468-byte element of [first, last) to dest (operator= 0x9b3490); returns the end of the destination.
#include "game/types.h"

struct Elem_9b4310 {
    char mData[0x468];
    Elem_9b4310& operator=(const Elem_9b4310& o);   // 0x009b3490
};

// @ 0x009b4310
Elem_9b4310* Copy_9b4310(const Elem_9b4310* first, const Elem_9b4310* last, Elem_9b4310* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
