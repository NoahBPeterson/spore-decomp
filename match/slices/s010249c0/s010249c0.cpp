// uninitialized_fill_n (0x010249c0): copy-construct n 0x1c-byte elements from value into raw storage (copy constructor 0x7d0ac0).
#include "game/types.h"

struct Elem_10249c0 {
    char mData[0x1c];
    Elem_10249c0(const Elem_10249c0& o);   // 0x007d0ac0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x010249c0
void UninitializedFillN_10249c0(Elem_10249c0* first, unsigned n, const Elem_10249c0& value)
{
    Elem_10249c0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_10249c0(value);
}
