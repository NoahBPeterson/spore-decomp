// fill (0x0106cc40): assign value to each 0x28-byte element of [first, last) (operator= 0x10685a0).
#include "game/types.h"

struct Elem_106cc40 {
    char mData[0x28];
    Elem_106cc40& operator=(const Elem_106cc40& o);   // 0x010685a0
};

// @ 0x0106cc40
void Fill_106cc40(Elem_106cc40* first, Elem_106cc40* last, const Elem_106cc40& value)
{
    for (; first != last; ++first)
        *first = value;
}
