// uninitialized_fill_n (0x0059ef70): copy-construct n 0x18-byte elements from value into raw storage (copy constructor 0x810020).
#include "game/types.h"

struct Elem_59ef70 {
    char mData[0x18];
    Elem_59ef70(const Elem_59ef70& o);   // 0x00810020
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x0059ef70
void UninitializedFillN_59ef70(Elem_59ef70* first, unsigned n, const Elem_59ef70& value)
{
    Elem_59ef70* cur = first;
    for (; n > 0; --n, ++cur)
        new (cur) Elem_59ef70(value);
}
