// uninitialized_fill_n (0x00cd7d60): copy-construct n 0x14-byte elements from value into raw storage (copy constructor 0x473460).
#include "game/types.h"

struct Elem_cd7d60 {
    char mData[0x14];
    Elem_cd7d60(const Elem_cd7d60& o);   // 0x00473460
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00cd7d60
void UninitializedFillN_cd7d60(Elem_cd7d60* first, unsigned n, const Elem_cd7d60& value)
{
    Elem_cd7d60* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_cd7d60(value);
}
