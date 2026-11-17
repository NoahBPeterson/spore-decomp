// uninitialized_fill_n (0x007f7a30): copy-construct n 0x8c-byte elements from value into raw storage (copy constructor 0x7f6df0).
#include "game/types.h"

struct Elem_7f7a30 {
    char mData[0x8c];
    Elem_7f7a30(const Elem_7f7a30& o);   // 0x007f6df0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x007f7a30
void UninitializedFillN_7f7a30(Elem_7f7a30* first, unsigned n, const Elem_7f7a30& value)
{
    Elem_7f7a30* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_7f7a30(value);
}
