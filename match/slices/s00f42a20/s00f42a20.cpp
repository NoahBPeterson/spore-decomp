// fill (0x00f42a20): assign value to each 0x4e0-byte element of [first, last) (operator= 0xdfcce0).
#include "game/types.h"

struct Elem_f42a20 {
    char mData[0x4e0];
    Elem_f42a20& operator=(const Elem_f42a20& o);   // 0x00dfcce0
};

// @ 0x00f42a20
void Fill_f42a20(Elem_f42a20* first, Elem_f42a20* last, const Elem_f42a20& value)
{
    for (; first != last; ++first)
        *first = value;
}
