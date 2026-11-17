// fill (0x00a84820): assign value to each 0x84-byte element of [first, last) (operator= 0xa6ac70).
#include "game/types.h"

struct Elem_a84820 {
    char mData[0x84];
    Elem_a84820& operator=(const Elem_a84820& o);   // 0x00a6ac70
};

// @ 0x00a84820
void Fill_a84820(Elem_a84820* first, Elem_a84820* last, const Elem_a84820& value)
{
    for (; first != last; ++first)
        *first = value;
}
