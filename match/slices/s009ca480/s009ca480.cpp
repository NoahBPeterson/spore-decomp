// fill (0x009ca480): assign value to each 0x468-byte element of [first, last) (operator= 0x9b3490).
#include "game/types.h"

struct Elem_9ca480 {
    char mData[0x468];
    Elem_9ca480& operator=(const Elem_9ca480& o);   // 0x009b3490
};

// @ 0x009ca480
void Fill_9ca480(Elem_9ca480* first, Elem_9ca480* last, const Elem_9ca480& value)
{
    for (; first != last; ++first)
        *first = value;
}
