// uninitialized_fill_n (0x00aa1ec0): copy-construct n 0x28-byte elements from value into raw storage (copy constructor 0xaa1cc0).
#include "game/types.h"

struct Elem_aa1ec0 {
    char mData[0x28];
    Elem_aa1ec0(const Elem_aa1ec0& o);   // 0x00aa1cc0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00aa1ec0
void UninitializedFillN_aa1ec0(Elem_aa1ec0* first, unsigned n, const Elem_aa1ec0& value)
{
    Elem_aa1ec0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_aa1ec0(value);
}
