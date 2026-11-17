// copy_backward (0x009bf640): assign the 0x2bc-byte elements of [first, last) backwards so they end at resultEnd (operator= 0x9bf210).
#include "game/types.h"

struct Elem_9bf640 {
    char mData[0x2bc];
    Elem_9bf640& operator=(const Elem_9bf640& o);   // 0x009bf210
};

// @ 0x009bf640
Elem_9bf640* CopyBackward_9bf640(const Elem_9bf640* first, const Elem_9bf640* last, Elem_9bf640* resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
