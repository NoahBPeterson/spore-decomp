// copy (0x00baa8b0): assign each 0x14-byte element of [first, last) to dest (operator= 0x1011cc0); returns the end of the destination.
#include "game/types.h"

struct Elem_baa8b0 {
    char mData[0x14];
    Elem_baa8b0& operator=(const Elem_baa8b0& o);   // 0x01011cc0
};

// @ 0x00baa8b0
Elem_baa8b0* Copy_baa8b0(const Elem_baa8b0* first, const Elem_baa8b0* last, Elem_baa8b0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
