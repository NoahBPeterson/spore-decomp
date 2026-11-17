// fill (0x0079fcf0): assign value to each 0x14-byte element of [first, last) (operator= 0x79f640).
#include "game/types.h"

struct Elem_79fcf0 {
    char mData[0x14];
    Elem_79fcf0& operator=(const Elem_79fcf0& o);   // 0x0079f640
};

// @ 0x0079fcf0
void Fill_79fcf0(Elem_79fcf0* first, Elem_79fcf0* last, const Elem_79fcf0& value)
{
    for (; first != last; ++first)
        *first = value;
}
