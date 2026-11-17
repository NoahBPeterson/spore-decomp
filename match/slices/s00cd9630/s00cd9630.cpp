// fill (0x00cd9630): assign value to each 0x14-byte element of [first, last) (operator= 0x473500).
#include "game/types.h"

struct Elem_cd9630 {
    char mData[0x14];
    Elem_cd9630& operator=(const Elem_cd9630& o);   // 0x00473500
};

// @ 0x00cd9630
void Fill_cd9630(Elem_cd9630* first, Elem_cd9630* last, const Elem_cd9630& value)
{
    for (; first != last; ++first)
        *first = value;
}
