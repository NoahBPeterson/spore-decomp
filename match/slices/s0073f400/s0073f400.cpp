// copy_backward (0x0073f400): assign the 0xc4-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x73f320).
#include "game/types.h"

struct Elem_73f400 {
    char mData[0xc4];
    Elem_73f400& operator=(const Elem_73f400& o);   // 0x0073f320
};

// @ 0x0073f400
Elem_73f400* CopyBackward_73f400(const Elem_73f400* first, const Elem_73f400* last, Elem_73f400* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
