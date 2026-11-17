// uninitialized_fill_n (0x00a09cc0): copy-construct n 0x1c-byte elements from value into raw storage (copy constructor 0xa093b0).
#include "game/types.h"

struct Elem_a09cc0 {
    char mData[0x1c];
    Elem_a09cc0(const Elem_a09cc0& o);   // 0x00a093b0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a09cc0
void UninitializedFillN_a09cc0(Elem_a09cc0* first, unsigned n, const Elem_a09cc0& value)
{
    Elem_a09cc0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_a09cc0(value);
}
