// copy (0x00bc6570): assign each 0x7b4-byte element of [first, last) to dest (operator= 0xbc6360); returns the end of the destination.
#include "game/types.h"

struct Elem_bc6570 {
    char mData[0x7b4];
    Elem_bc6570& operator=(const Elem_bc6570& o);   // 0x00bc6360
};

// @ 0x00bc6570
Elem_bc6570* Copy_bc6570(const Elem_bc6570* first, const Elem_bc6570* last, Elem_bc6570* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
