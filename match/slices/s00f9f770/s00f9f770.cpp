// copy (0x00f9f770): assign each 0xac-byte element of [first, last) to dest (operator= 0xf9f620); returns the end of the destination.
#include "game/types.h"

struct Elem_f9f770 {
    char mData[0xac];
    Elem_f9f770& operator=(const Elem_f9f770& o);   // 0x00f9f620
};

// @ 0x00f9f770
Elem_f9f770* Copy_f9f770(const Elem_f9f770* first, const Elem_f9f770* last, Elem_f9f770* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
