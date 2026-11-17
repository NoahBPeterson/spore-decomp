// copy (0x0104f170): assign each 0x14-byte element of [first, last) to dest (operator= 0x6609a0); returns the end of the destination.
#include "game/types.h"

struct Elem_104f170 {
    char mData[0x14];
    Elem_104f170& operator=(const Elem_104f170& o);   // 0x006609a0
};

// @ 0x0104f170
Elem_104f170* Copy_104f170(const Elem_104f170* first, const Elem_104f170* last, Elem_104f170* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
