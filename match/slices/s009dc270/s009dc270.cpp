// copy (0x009dc270): assign each 0x58-byte element of [first, last) to dest (operator= 0x9dc050); returns the end of the destination.
#include "game/types.h"

struct Elem_9dc270 {
    char mData[0x58];
    Elem_9dc270& operator=(const Elem_9dc270& o);   // 0x009dc050
};

// @ 0x009dc270
Elem_9dc270* Copy_9dc270(const Elem_9dc270* first, const Elem_9dc270* last, Elem_9dc270* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
