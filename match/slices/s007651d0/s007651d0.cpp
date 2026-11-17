// fill (0x007651d0): assign value to each 0xa0-byte element of [first, last) (operator= 0x700290).
#include "game/types.h"

struct Elem_7651d0 {
    char mData[0xa0];
    Elem_7651d0& operator=(const Elem_7651d0& o);   // 0x00700290
};

// @ 0x007651d0
void Fill_7651d0(Elem_7651d0* first, Elem_7651d0* last, const Elem_7651d0& value)
{
    for (; first != last; ++first)
        *first = value;
}
