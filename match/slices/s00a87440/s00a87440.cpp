// uninitialized_fill_n (0x00a87440): copy-construct n 0x58-byte elements from value into raw storage (copy constructor 0xa87280).
#include "game/types.h"

struct Elem_a87440 {
    char mData[0x58];
    Elem_a87440(const Elem_a87440& o);   // 0x00a87280
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a87440
void UninitializedFillN_a87440(Elem_a87440* first, unsigned n, const Elem_a87440& value)
{
    Elem_a87440* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_a87440(value);
}
