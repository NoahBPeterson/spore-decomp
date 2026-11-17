// copy_backward (0x00673a50): assign the 0x63c-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x673940).
#include "game/types.h"

struct Elem_673a50 {
    char mData[0x63c];
    Elem_673a50& operator=(const Elem_673a50& o);   // 0x00673940
};

// @ 0x00673a50
Elem_673a50* CopyBackward_673a50(const Elem_673a50* first, const Elem_673a50* last, Elem_673a50* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
