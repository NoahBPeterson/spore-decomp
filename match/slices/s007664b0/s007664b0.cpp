// fill (0x007664b0): assign value to each 0x7c-byte element of [first, last) (operator= 0x429370).
#include "game/types.h"

struct Elem_7664b0 {
    char mData[0x7c];
    Elem_7664b0& operator=(const Elem_7664b0& o);   // 0x00429370
};

// @ 0x007664b0
void Fill_7664b0(Elem_7664b0* first, Elem_7664b0* last, const Elem_7664b0& value)
{
    for (; first != last; ++first)
        *first = value;
}
