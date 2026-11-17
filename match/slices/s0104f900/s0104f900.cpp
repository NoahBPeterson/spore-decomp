// fill (0x0104f900): assign value to each 0x14-byte element of [first, last) (operator= 0x6609a0).
#include "game/types.h"

struct Elem_104f900 {
    char mData[0x14];
    Elem_104f900& operator=(const Elem_104f900& o);   // 0x006609a0
};

// @ 0x0104f900
void Fill_104f900(Elem_104f900* first, Elem_104f900* last, const Elem_104f900& value)
{
    for (; first != last; ++first)
        *first = value;
}
