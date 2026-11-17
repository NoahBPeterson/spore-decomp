// fill (0x009c0d40): assign value to each 0x10c-byte element of [first, last) (operator= 0x9befa0).
#include "game/types.h"

struct Elem_9c0d40 {
    char mData[0x10c];
    Elem_9c0d40& operator=(const Elem_9c0d40& o);   // 0x009befa0
};

// @ 0x009c0d40
void Fill_9c0d40(Elem_9c0d40* first, Elem_9c0d40* last, const Elem_9c0d40& value)
{
    for (; first != last; ++first)
        *first = value;
}
