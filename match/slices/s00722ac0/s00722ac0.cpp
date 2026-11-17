// copy_backward (0x00722ac0): assign the 0x64-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x7229f0).
#include "game/types.h"

struct Elem_722ac0 {
    char mData[0x64];
    Elem_722ac0& operator=(const Elem_722ac0& o);   // 0x007229f0
};

// @ 0x00722ac0
Elem_722ac0* CopyBackward_722ac0(const Elem_722ac0* first, const Elem_722ac0* last, Elem_722ac0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
