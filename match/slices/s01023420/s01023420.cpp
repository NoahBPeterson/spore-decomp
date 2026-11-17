// copy (0x01023420): assign each 0x1c-byte element of [first, last) to dest (operator= 0x7d0b80); returns the end of the destination.
#include "game/types.h"

struct Elem_1023420 {
    char mData[0x1c];
    Elem_1023420& operator=(const Elem_1023420& o);   // 0x007d0b80
};

// @ 0x01023420
Elem_1023420* Copy_1023420(const Elem_1023420* first, const Elem_1023420* last, Elem_1023420* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
