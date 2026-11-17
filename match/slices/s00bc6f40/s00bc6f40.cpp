// fill (0x00bc6f40): assign value to each 0x7b4-byte element of [first, last) (operator= 0xbc6360).
#include "game/types.h"

struct Elem_bc6f40 {
    char mData[0x7b4];
    Elem_bc6f40& operator=(const Elem_bc6f40& o);   // 0x00bc6360
};

// @ 0x00bc6f40
void Fill_bc6f40(Elem_bc6f40* first, Elem_bc6f40* last, const Elem_bc6f40& value)
{
    for (; first != last; ++first)
        *first = value;
}
