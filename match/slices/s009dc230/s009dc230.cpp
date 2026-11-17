// copy (0x009dc230): assign each 0x44-byte element of [first, last) to dest (operator= 0x9dbfd0); returns the end of the destination.
#include "game/types.h"

struct Elem_9dc230 {
    char mData[0x44];
    Elem_9dc230& operator=(const Elem_9dc230& o);   // 0x009dbfd0
};

// @ 0x009dc230
Elem_9dc230* Copy_9dc230(const Elem_9dc230* first, const Elem_9dc230* last, Elem_9dc230* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
