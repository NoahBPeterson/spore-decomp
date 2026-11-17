// uninitialized_fill_n (0x00eaff90): copy-construct n 0x6c-byte elements from value into raw storage (copy constructor 0xeaf190).
#include "game/types.h"

struct Elem_eaff90 {
    char mData[0x6c];
    Elem_eaff90(const Elem_eaff90& o);   // 0x00eaf190
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00eaff90
void UninitializedFillN_eaff90(Elem_eaff90* first, unsigned n, const Elem_eaff90& value)
{
    Elem_eaff90* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_eaff90(value);
}
