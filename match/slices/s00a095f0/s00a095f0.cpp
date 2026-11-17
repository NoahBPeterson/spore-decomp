// uninitialized_copy (0x00a095f0): copy-construct each 0x1c-byte element of [first, last) into raw storage at dest
// (copy constructor 0xa093b0); returns the end of the copied range.
#include "game/types.h"

struct Elem_a095f0 {
    char mData[0x1c];
    Elem_a095f0(const Elem_a095f0& o);   // 0x00a093b0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00a095f0
Elem_a095f0* UninitializedCopy_a095f0(const Elem_a095f0* first, const Elem_a095f0* last, Elem_a095f0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_a095f0(*first);
    return dest;
}
