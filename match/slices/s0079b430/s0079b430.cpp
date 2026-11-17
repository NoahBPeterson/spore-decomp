// copy (0x0079b430): assign each 0x14-byte element of [first, last) to dest (operator= 0x79b360); returns the end of the destination.
#include "game/types.h"

struct Elem_79b430 {
    char mData[0x14];
    Elem_79b430& operator=(const Elem_79b430& o);   // 0x0079b360
};

// @ 0x0079b430
Elem_79b430* Copy_79b430(const Elem_79b430* first, const Elem_79b430* last, Elem_79b430* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
