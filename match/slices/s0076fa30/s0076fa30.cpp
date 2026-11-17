// copy (0x0076fa30): assign each 0xb0-byte element of [first, last) to dest (operator= 0x76f580); returns the end of the destination.
#include "game/types.h"

struct Elem_76fa30 {
    char mData[0xb0];
    Elem_76fa30& operator=(const Elem_76fa30& o);   // 0x0076f580
};

// @ 0x0076fa30
Elem_76fa30* Copy_76fa30(const Elem_76fa30* first, const Elem_76fa30* last, Elem_76fa30* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
