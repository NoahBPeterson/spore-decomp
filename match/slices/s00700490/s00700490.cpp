// copy (0x00700490): assign each 0x7c-byte element of [first, last) to dest (operator= 0x429370); returns the end of the destination.
#include "game/types.h"

struct Elem_700490 {
    char mData[0x7c];
    Elem_700490& operator=(const Elem_700490& o);   // 0x00429370
};

// @ 0x00700490
Elem_700490* Copy_700490(const Elem_700490* first, const Elem_700490* last, Elem_700490* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
