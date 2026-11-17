// uninitialized_fill_n (0x00e2ad70): copy-construct n 0x14-byte elements from value into raw storage (copy constructor 0x6b56f0).
#include "game/types.h"

struct Elem_e2ad70 {
    char mData[0x14];
    Elem_e2ad70(const Elem_e2ad70& o);   // 0x006b56f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00e2ad70
void UninitializedFillN_e2ad70(Elem_e2ad70* first, unsigned n, const Elem_e2ad70& value)
{
    Elem_e2ad70* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_e2ad70(value);
}
