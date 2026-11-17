// uninitialized_fill_n (0x00f42e30): copy-construct n 0x4e0-byte elements from value into raw storage (copy constructor 0xdfd080).
#include "game/types.h"

struct Elem_f42e30 {
    char mData[0x4e0];
    Elem_f42e30(const Elem_f42e30& o);   // 0x00dfd080
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f42e30
void UninitializedFillN_f42e30(Elem_f42e30* first, unsigned n, const Elem_f42e30& value)
{
    Elem_f42e30* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_f42e30(value);
}
