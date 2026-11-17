// uninitialized_fill_n (0x00f16230): copy-construct n 0x70-byte elements from value into raw storage (copy constructor 0xf14690).
#include "game/types.h"

struct Elem_f16230 {
    char mData[0x70];
    Elem_f16230(const Elem_f16230& o);   // 0x00f14690
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f16230
void UninitializedFillN_f16230(Elem_f16230* first, unsigned n, const Elem_f16230& value)
{
    Elem_f16230* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_f16230(value);
}
