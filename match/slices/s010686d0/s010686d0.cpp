// copy (0x010686d0): assign each 0x28-byte element of [first, last) to dest (operator= 0x10685a0); returns the end of the destination.
#include "game/types.h"

struct Elem_10686d0 {
    char mData[0x28];
    Elem_10686d0& operator=(const Elem_10686d0& o);   // 0x010685a0
};

// @ 0x010686d0
Elem_10686d0* Copy_10686d0(const Elem_10686d0* first, const Elem_10686d0* last, Elem_10686d0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
