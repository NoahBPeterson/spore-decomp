// uninitialized_fill_n (0x009c0ad0): copy-construct n 0x2bc-byte elements from value into raw storage (copy constructor 0x9bea50).
#include "game/types.h"

struct Elem_9c0ad0 {
    char mData[0x2bc];
    Elem_9c0ad0(const Elem_9c0ad0& o);   // 0x009bea50
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009c0ad0
void UninitializedFillN_9c0ad0(Elem_9c0ad0* first, unsigned n, const Elem_9c0ad0& value)
{
    Elem_9c0ad0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_9c0ad0(value);
}
