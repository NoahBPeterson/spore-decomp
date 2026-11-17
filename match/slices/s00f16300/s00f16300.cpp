// fill (0x00f16300): assign value to each 0x70-byte element of [first, last) (operator= 0xf147e0).
#include "game/types.h"

struct Elem_f16300 {
    char mData[0x70];
    Elem_f16300& operator=(const Elem_f16300& o);   // 0x00f147e0
};

// @ 0x00f16300
void Fill_f16300(Elem_f16300* first, Elem_f16300* last, const Elem_f16300& value)
{
    for (; first != last; ++first)
        *first = value;
}
