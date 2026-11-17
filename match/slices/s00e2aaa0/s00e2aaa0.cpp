// fill (0x00e2aaa0): assign value to each 0x14-byte element of [first, last) (operator= 0x6b5430).
#include "game/types.h"

struct Elem_e2aaa0 {
    char mData[0x14];
    Elem_e2aaa0& operator=(const Elem_e2aaa0& o);   // 0x006b5430
};

// @ 0x00e2aaa0
void Fill_e2aaa0(Elem_e2aaa0* first, Elem_e2aaa0* last, const Elem_e2aaa0& value)
{
    for (; first != last; ++first)
        *first = value;
}
