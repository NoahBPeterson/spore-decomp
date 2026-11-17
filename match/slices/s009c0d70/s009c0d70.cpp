// fill (0x009c0d70): assign value to each 0x2bc-byte element of [first, last) (operator= 0x9bf210).
#include "game/types.h"

struct Elem_9c0d70 {
    char mData[0x2bc];
    Elem_9c0d70& operator=(const Elem_9c0d70& o);   // 0x009bf210
};

// @ 0x009c0d70
void Fill_9c0d70(Elem_9c0d70* first, Elem_9c0d70* last, const Elem_9c0d70& value)
{
    for (; first != last; ++first)
        *first = value;
}
