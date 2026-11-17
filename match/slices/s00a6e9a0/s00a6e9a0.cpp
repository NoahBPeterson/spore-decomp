// uninitialized_copy (0x00a6e9a0): copy-construct each 0x84-byte element of [first, last) into raw storage at dest
// (copy constructor 0xa6a2f0); returns the end of the copied range.
#include "game/types.h"

struct Elem_a6e9a0 {
    char mData[0x84];
    Elem_a6e9a0(const Elem_a6e9a0& o);   // 0x00a6a2f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a6e9a0
Elem_a6e9a0* UninitializedCopy_a6e9a0(const Elem_a6e9a0* first, const Elem_a6e9a0* last, Elem_a6e9a0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_a6e9a0(*first);
    return dest;
}
