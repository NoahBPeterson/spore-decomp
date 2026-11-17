// uninitialized_fill_n (0x00a847f0): copy-construct n 0x84-byte elements from value into raw storage (copy constructor 0xa6a2f0).
#include "game/types.h"

struct Elem_a847f0 {
    char mData[0x84];
    Elem_a847f0(const Elem_a847f0& o);   // 0x00a6a2f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a847f0
void UninitializedFillN_a847f0(Elem_a847f0* first, unsigned n, const Elem_a847f0& value)
{
    Elem_a847f0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_a847f0(value);
}
