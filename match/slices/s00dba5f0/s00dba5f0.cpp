// copy_backward (0x00dba5f0): assign the 0x250-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xdba580).
#include "game/types.h"

struct Elem_dba5f0 {
    char mData[0x250];
    Elem_dba5f0& operator=(const Elem_dba5f0& o);   // 0x00dba580
};

// @ 0x00dba5f0
Elem_dba5f0* CopyBackward_dba5f0(const Elem_dba5f0* first, const Elem_dba5f0* last, Elem_dba5f0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
