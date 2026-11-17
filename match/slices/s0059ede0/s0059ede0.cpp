// copy (0x0059ede0): assign each 0x18-byte element of [first, last) to dest (operator= 0x810050); returns the end of the destination.
#include "game/types.h"

struct Elem_59ede0 {
    char mData[0x18];
    Elem_59ede0& operator=(const Elem_59ede0& o);   // 0x00810050
};

// @ 0x0059ede0
Elem_59ede0* Copy_59ede0(const Elem_59ede0* first, const Elem_59ede0* last, Elem_59ede0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
