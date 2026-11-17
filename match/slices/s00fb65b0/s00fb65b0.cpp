// copy (0x00fb65b0): assign each 0x110-byte element of [first, last) to dest (operator= 0xfa99c0); returns the end of the destination.
#include "game/types.h"

struct Elem_fb65b0 {
    char mData[0x110];
    Elem_fb65b0& operator=(const Elem_fb65b0& o);   // 0x00fa99c0
};

// @ 0x00fb65b0
Elem_fb65b0* Copy_fb65b0(const Elem_fb65b0* first, const Elem_fb65b0* last, Elem_fb65b0* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
