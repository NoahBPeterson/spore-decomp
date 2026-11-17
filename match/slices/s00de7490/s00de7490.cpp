// uninitialized_fill_n (0x00de7490): copy-construct n 0xbc-byte elements from value into raw storage (copy constructor 0xde60f0).
#include "game/types.h"

struct Elem_de7490 {
    char mData[0xbc];
    Elem_de7490(const Elem_de7490& o);   // 0x00de60f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00de7490
void UninitializedFillN_de7490(Elem_de7490* first, unsigned n, const Elem_de7490& value)
{
    Elem_de7490* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_de7490(value);
}
