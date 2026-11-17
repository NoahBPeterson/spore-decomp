// uninitialized_fill_n (0x009a1bf0): copy-construct n 0x1f0-byte elements from value into raw storage (copy constructor 0x9a17d0).
#include "game/types.h"

struct Elem_9a1bf0 {
    char mData[0x1f0];
    Elem_9a1bf0(const Elem_9a1bf0& o);   // 0x009a17d0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x009a1bf0
void UninitializedFillN_9a1bf0(Elem_9a1bf0* first, unsigned n, const Elem_9a1bf0& value)
{
    Elem_9a1bf0* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_9a1bf0(value);
}
