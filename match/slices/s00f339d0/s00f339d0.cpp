// copy (0x00f339d0): assign each 0x38-byte element of [first, last) to dest (operator= 0x537dc0); returns the end of the destination.
#include "game/types.h"

struct Elem_f339d0 {
    char mData[0x38];
    Elem_f339d0& operator=(const Elem_f339d0& o);   // 0x00537dc0
};

// @ 0x00f339d0
Elem_f339d0* Copy_f339d0(const Elem_f339d0* first, const Elem_f339d0* last, Elem_f339d0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
