// copy (0x00dff270): assign each 0x534-byte element of [first, last) to dest (operator= 0xdfedb0); returns the end of the destination.
#include "game/types.h"

struct Elem_dff270 {
    char mData[0x534];
    Elem_dff270& operator=(const Elem_dff270& o);   // 0x00dfedb0
};

// @ 0x00dff270
Elem_dff270* Copy_dff270(const Elem_dff270* first, const Elem_dff270* last, Elem_dff270* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
