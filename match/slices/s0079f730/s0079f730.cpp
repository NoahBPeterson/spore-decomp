// copy (0x0079f730): assign each 0x14-byte element of [first, last) to dest (operator= 0x79f640); returns the end of the destination.
#include "game/types.h"

struct Elem_79f730 {
    char mData[0x14];
    Elem_79f730& operator=(const Elem_79f730& o);   // 0x0079f640
};

// @ 0x0079f730
Elem_79f730* Copy_79f730(const Elem_79f730* first, const Elem_79f730* last, Elem_79f730* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
