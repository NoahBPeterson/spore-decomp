// uninitialized_fill_n (0x00765200): copy-construct n 0xa0-byte elements from value into raw storage (copy constructor 0x763e50).
#include "game/types.h"

struct Elem_765200 {
    char mData[0xa0];
    Elem_765200(const Elem_765200& o);   // 0x00763e50
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00765200
void UninitializedFillN_765200(Elem_765200* first, unsigned n, const Elem_765200& value)
{
    Elem_765200* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_765200(value);
}
