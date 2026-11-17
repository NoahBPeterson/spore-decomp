// fill (0x00723bf0): assign value to each 0x64-byte element of [first, last) (operator= 0x7229f0).
#include "game/types.h"

struct Elem_723bf0 {
    char mData[0x64];
    Elem_723bf0& operator=(const Elem_723bf0& o);   // 0x007229f0
};

// @ 0x00723bf0
void Fill_723bf0(Elem_723bf0* first, Elem_723bf0* last, const Elem_723bf0& value)
{
    for (; first != last; ++first)
        *first = value;
}
