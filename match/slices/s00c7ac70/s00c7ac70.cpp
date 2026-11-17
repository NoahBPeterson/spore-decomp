// fill (0x00c7ac70): assign value to each 0x14-byte element of [first, last) (operator= 0xdb5b30).
#include "game/types.h"

struct Elem_c7ac70 {
    char mData[0x14];
    Elem_c7ac70& operator=(const Elem_c7ac70& o);   // 0x00db5b30
};

// @ 0x00c7ac70
void Fill_c7ac70(Elem_c7ac70* first, Elem_c7ac70* last, const Elem_c7ac70& value)
{
    for (; first != last; ++first)
        *first = value;
}
