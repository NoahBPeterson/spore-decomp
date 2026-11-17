// uninitialized_fill_n (0x0104f140): copy-construct n 0x14-byte elements from value into raw storage (copy constructor 0x6606a0).
#include "game/types.h"

struct Elem_104f140 {
    char mData[0x14];
    Elem_104f140(const Elem_104f140& o);   // 0x006606a0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0104f140
void UninitializedFillN_104f140(Elem_104f140* first, unsigned n, const Elem_104f140& value)
{
    Elem_104f140* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_104f140(value);
}
