// fill (0x00a87810): assign value to each 0x58-byte element of [first, last) (operator= 0xa873c0).
#include "game/types.h"

struct Elem_a87810 {
    char mData[0x58];
    Elem_a87810& operator=(const Elem_a87810& o);   // 0x00a873c0
};

// @ 0x00a87810
void Fill_a87810(Elem_a87810* first, Elem_a87810* last, const Elem_a87810& value)
{
    for (; first != last; ++first)
        *first = value;
}
