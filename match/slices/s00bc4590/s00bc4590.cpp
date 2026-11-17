// fill (0x00bc4590): assign value to each 0x98-byte element of [first, last) (operator= 0xbc3f50).
#include "game/types.h"

struct Elem_bc4590 {
    char mData[0x98];
    Elem_bc4590& operator=(const Elem_bc4590& o);   // 0x00bc3f50
};

// @ 0x00bc4590
void Fill_bc4590(Elem_bc4590* first, Elem_bc4590* last, const Elem_bc4590& value)
{
    for (; first != last; ++first)
        *first = value;
}
