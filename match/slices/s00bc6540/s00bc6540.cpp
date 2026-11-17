// uninitialized_fill_n (0x00bc6540): copy-construct n 0x7b4-byte elements from value into raw storage (copy constructor 0xbc54f0).
#include "game/types.h"

struct Elem_bc6540 {
    char mData[0x7b4];
    Elem_bc6540(const Elem_bc6540& o);   // 0x00bc54f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00bc6540
void UninitializedFillN_bc6540(Elem_bc6540* first, unsigned n, const Elem_bc6540& value)
{
    Elem_bc6540* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_bc6540(value);
}
