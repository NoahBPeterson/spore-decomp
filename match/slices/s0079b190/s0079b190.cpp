// fill (0x0079b190): assign value to each 0x14-byte element of [first, last) (operator= 0x7552e0).
#include "game/types.h"

struct Elem_79b190 {
    char mData[0x14];
    Elem_79b190& operator=(const Elem_79b190& o);   // 0x007552e0
};

// @ 0x0079b190
void Fill_79b190(Elem_79b190* first, Elem_79b190* last, const Elem_79b190& value)
{
    for (; first != last; ++first)
        *first = value;
}
