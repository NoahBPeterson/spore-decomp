// fill (0x009a1eb0): assign value to each 0x1f0-byte element of [first, last) (operator= 0x9a18a0).
#include "game/types.h"

struct Elem_9a1eb0 {
    char mData[0x1f0];
    Elem_9a1eb0& operator=(const Elem_9a1eb0& o);   // 0x009a18a0
};

// @ 0x009a1eb0
void Fill_9a1eb0(Elem_9a1eb0* first, Elem_9a1eb0* last, const Elem_9a1eb0& value)
{
    for (; first != last; ++first)
        *first = value;
}
