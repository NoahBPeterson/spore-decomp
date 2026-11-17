// fill (0x0079fcc0): assign value to each 0x14-byte element of [first, last) (operator= 0x79b360).
#include "game/types.h"

struct Elem_79fcc0 {
    char mData[0x14];
    Elem_79fcc0& operator=(const Elem_79fcc0& o);   // 0x0079b360
};

// @ 0x0079fcc0
void Fill_79fcc0(Elem_79fcc0* first, Elem_79fcc0* last, const Elem_79fcc0& value)
{
    for (; first != last; ++first)
        *first = value;
}
