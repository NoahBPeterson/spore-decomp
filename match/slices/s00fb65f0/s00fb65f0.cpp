// copy_backward (0x00fb65f0): assign the 0x110-byte elements of [first, last) backwards so they end at resultEnd (operator= 0xfa99c0).
#include "game/types.h"

struct Elem_fb65f0 {
    char mData[0x110];
    Elem_fb65f0& operator=(const Elem_fb65f0& o);   // 0x00fa99c0
};

// @ 0x00fb65f0
Elem_fb65f0* CopyBackward_fb65f0(const Elem_fb65f0* first, const Elem_fb65f0* last, Elem_fb65f0* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
