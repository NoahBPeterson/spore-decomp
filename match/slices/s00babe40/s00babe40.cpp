// fill (0x00babe40): assign value to each 0x14-byte element of [first, last) (operator= 0x1011cc0).
#include "game/types.h"

struct Elem_babe40 {
    char mData[0x14];
    Elem_babe40& operator=(const Elem_babe40& o);   // 0x01011cc0
};

// @ 0x00babe40
void Fill_babe40(Elem_babe40* first, Elem_babe40* last, const Elem_babe40& value)
{
    for (; first != last; ++first)
        *first = value;
}
