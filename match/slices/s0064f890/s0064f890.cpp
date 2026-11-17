// copy (0x0064f890): assign each 0x20-byte element of [first, last) to dest (operator= 0x64f450); returns the end of the destination.
#include "game/types.h"

struct Elem_64f890 {
    char mData[0x20];
    Elem_64f890& operator=(const Elem_64f890& o);   // 0x0064f450
};

// @ 0x0064f890
Elem_64f890* Copy_64f890(const Elem_64f890* first, const Elem_64f890* last, Elem_64f890* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
