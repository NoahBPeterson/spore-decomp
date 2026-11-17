// fill (0x00a6bcc0): assign value to each 0x58-byte element of [first, last) (operator= 0xa6bb80).
#include "game/types.h"

struct Elem_a6bcc0 {
    char mData[0x58];
    Elem_a6bcc0& operator=(const Elem_a6bcc0& o);   // 0x00a6bb80
};

// @ 0x00a6bcc0
void Fill_a6bcc0(Elem_a6bcc0* first, Elem_a6bcc0* last, const Elem_a6bcc0& value)
{
    for (; first != last; ++first)
        *first = value;
}
