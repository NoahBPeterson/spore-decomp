// fill (0x007191d0): assign value to each 0xd0-byte element of [first, last) (operator= 0x7179e0).
#include "game/types.h"

struct Elem_7191d0 {
    char mData[0xd0];
    Elem_7191d0& operator=(const Elem_7191d0& o);   // 0x007179e0
};

// @ 0x007191d0
void Fill_7191d0(Elem_7191d0* first, Elem_7191d0* last, const Elem_7191d0& value)
{
    for (; first != last; ++first)
        *first = value;
}
