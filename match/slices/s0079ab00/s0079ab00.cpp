// copy (0x0079ab00): assign each 0x14-byte element of [first, last) to dest (operator= 0x7552e0); returns the end of the destination.
#include "game/types.h"

struct Elem_79ab00 {
    char mData[0x14];
    Elem_79ab00& operator=(const Elem_79ab00& o);   // 0x007552e0
};

// @ 0x0079ab00
Elem_79ab00* Copy_79ab00(const Elem_79ab00* first, const Elem_79ab00* last, Elem_79ab00* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
