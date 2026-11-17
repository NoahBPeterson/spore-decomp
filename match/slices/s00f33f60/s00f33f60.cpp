// fill (0x00f33f60): assign value to each 0x38-byte element of [first, last) (operator= 0x537dc0).
#include "game/types.h"

struct Elem_f33f60 {
    char mData[0x38];
    Elem_f33f60& operator=(const Elem_f33f60& o);   // 0x00537dc0
};

// @ 0x00f33f60
void Fill_f33f60(Elem_f33f60* first, Elem_f33f60* last, const Elem_f33f60& value)
{
    for (; first != last; ++first)
        *first = value;
}
