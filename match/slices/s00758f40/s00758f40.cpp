// fill (0x00758f40): assign value to each 0x14-byte element of [first, last) (operator= 0x50d4e0).
#include "game/types.h"

struct Elem_758f40 {
    char mData[0x14];
    Elem_758f40& operator=(const Elem_758f40& o);   // 0x0050d4e0
};

// @ 0x00758f40
void Fill_758f40(Elem_758f40* first, Elem_758f40* last, const Elem_758f40& value)
{
    for (; first != last; ++first)
        *first = value;
}
