// copy (0x00dfd2c0): assign each 0x4e0-byte element of [first, last) to dest (operator= 0xdfcce0); returns the end of the destination.
#include "game/types.h"

struct Elem_dfd2c0 {
    char mData[0x4e0];
    Elem_dfd2c0& operator=(const Elem_dfd2c0& o);   // 0x00dfcce0
};

// @ 0x00dfd2c0
Elem_dfd2c0* Copy_dfd2c0(const Elem_dfd2c0* first, const Elem_dfd2c0* last, Elem_dfd2c0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
