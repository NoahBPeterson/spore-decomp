// uninitialized_fill_n (0x009c0aa0): copy-construct n 0x10c-byte elements from value into raw storage (copy constructor 0x9be850).
#include "game/types.h"

struct Elem_9c0aa0 {
    char mData[0x10c];
    Elem_9c0aa0(const Elem_9c0aa0& o);   // 0x009be850
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009c0aa0
void UninitializedFillN_9c0aa0(Elem_9c0aa0* first, unsigned n, const Elem_9c0aa0& value)
{
    Elem_9c0aa0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_9c0aa0(value);
}
