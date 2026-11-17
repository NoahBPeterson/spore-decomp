// fill (0x00651670): assign value to each 0x20-byte element of [first, last) (operator= 0x64f450).
#include "game/types.h"

struct Elem_651670 {
    char mData[0x20];
    Elem_651670& operator=(const Elem_651670& o);   // 0x0064f450
};

// @ 0x00651670
void Fill_651670(Elem_651670* first, Elem_651670* last, const Elem_651670& value)
{
    for (; first != last; ++first)
        *first = value;
}
