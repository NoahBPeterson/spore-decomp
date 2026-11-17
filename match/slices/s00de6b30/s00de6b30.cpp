// fill (0x00de6b30): assign value to each 0xbc-byte element of [first, last) (operator= 0xb26fb0).
#include "game/types.h"

struct Elem_de6b30 {
    char mData[0xbc];
    Elem_de6b30& operator=(const Elem_de6b30& o);   // 0x00b26fb0
};

// @ 0x00de6b30
void Fill_de6b30(Elem_de6b30* first, Elem_de6b30* last, const Elem_de6b30& value)
{
    for (; first != last; ++first)
        *first = value;
}
