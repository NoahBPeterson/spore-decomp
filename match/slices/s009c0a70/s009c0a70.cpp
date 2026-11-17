// uninitialized_fill_n (0x009c0a70): copy-construct n 0x468-byte elements from value into raw storage (copy constructor 0x9b3e40).
#include "game/types.h"

struct Elem_9c0a70 {
    char mData[0x468];
    Elem_9c0a70(const Elem_9c0a70& o);   // 0x009b3e40
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009c0a70
void UninitializedFillN_9c0a70(Elem_9c0a70* first, unsigned n, const Elem_9c0a70& value)
{
    Elem_9c0a70* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_9c0a70(value);
}
