// uninitialized_copy (0x00f2e2f0): copy-construct each 0x27e0-byte element of [first, last) into raw storage at dest
// (copy constructor 0xdff1a0); returns the end of the copied range.
#include "game/types.h"

struct Elem_f2e2f0 {
    char mData[0x27e0];
    Elem_f2e2f0(const Elem_f2e2f0& o);   // 0x00dff1a0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f2e2f0
Elem_f2e2f0* UninitializedCopy_f2e2f0(const Elem_f2e2f0* first, const Elem_f2e2f0* last, Elem_f2e2f0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_f2e2f0(*first);
    return dest;
}
