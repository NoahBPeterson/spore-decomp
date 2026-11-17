// fill (0x0059ef00): assign value to each 0x18-byte element of [first, last) (operator= 0x810050).
#include "game/types.h"

struct Elem_59ef00 {
    char mData[0x18];
    Elem_59ef00& operator=(const Elem_59ef00& o);   // 0x00810050
};

// @ 0x0059ef00
void Fill_59ef00(Elem_59ef00* first, Elem_59ef00* last, const Elem_59ef00& value)
{
    for (; first != last; ++first)
        *first = value;
}
