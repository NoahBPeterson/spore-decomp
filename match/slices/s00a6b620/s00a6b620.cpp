// uninitialized_fill_n (0x00a6b620): copy-construct n 0x58-byte elements from value into raw storage (copy constructor 0xa6b290).
#include "game/types.h"

struct Elem_a6b620 {
    char mData[0x58];
    Elem_a6b620(const Elem_a6b620& o);   // 0x00a6b290
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a6b620
void UninitializedFillN_a6b620(Elem_a6b620* first, unsigned n, const Elem_a6b620& value)
{
    Elem_a6b620* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_a6b620(value);
}
