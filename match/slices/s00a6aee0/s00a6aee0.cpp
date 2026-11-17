// fill (0x00a6aee0): assign value to each 0x14-byte element of [first, last) (operator= 0xa69e50).
#include "game/types.h"

struct Elem_a6aee0 {
    char mData[0x14];
    Elem_a6aee0& operator=(const Elem_a6aee0& o);   // 0x00a69e50
};

// @ 0x00a6aee0
void Fill_a6aee0(Elem_a6aee0* first, Elem_a6aee0* last, const Elem_a6aee0& value)
{
    for (; first != last; ++first)
        *first = value;
}
