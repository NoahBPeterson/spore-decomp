// copy (0x00763f50): assign each 0xa0-byte element of [first, last) to dest (operator= 0x700290); returns the end of the destination.
#include "game/types.h"

struct Elem_763f50 {
    char mData[0xa0];
    Elem_763f50& operator=(const Elem_763f50& o);   // 0x00700290
};

// @ 0x00763f50
Elem_763f50* Copy_763f50(const Elem_763f50* first, const Elem_763f50* last, Elem_763f50* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
