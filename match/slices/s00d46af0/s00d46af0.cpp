// copy (0x00d46af0): assign each 0x2c-byte element of [first, last) to dest (operator= 0xd46970); returns the end of the destination.
#include "game/types.h"

struct Elem_d46af0 {
    char mData[0x2c];
    Elem_d46af0& operator=(const Elem_d46af0& o);   // 0x00d46970
};

// @ 0x00d46af0
Elem_d46af0* Copy_d46af0(const Elem_d46af0* first, const Elem_d46af0* last, Elem_d46af0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
