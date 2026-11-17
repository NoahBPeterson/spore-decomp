// fill (0x01024e60): assign value to each 0x1c-byte element of [first, last) (operator= 0x7d0b80).
#include "game/types.h"

struct Elem_1024e60 {
    char mData[0x1c];
    Elem_1024e60& operator=(const Elem_1024e60& o);   // 0x007d0b80
};

// @ 0x01024e60
void Fill_1024e60(Elem_1024e60* first, Elem_1024e60* last, const Elem_1024e60& value)
{
    for (; first != last; ++first)
        *first = value;
}
