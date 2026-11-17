// fill (0x0070a270): assign value to each 0x144-byte element of [first, last) (operator= 0x7089a0).
#include "game/types.h"

struct Elem_70a270 {
    char mData[0x144];
    Elem_70a270& operator=(const Elem_70a270& o);   // 0x007089a0
};

// @ 0x0070a270
void Fill_70a270(Elem_70a270* first, Elem_70a270* last, const Elem_70a270& value)
{
    for (; first != last; ++first)
        *first = value;
}
