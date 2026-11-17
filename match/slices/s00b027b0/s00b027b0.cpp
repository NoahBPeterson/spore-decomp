// uninitialized_copy (0x00b027b0): copy-construct each 0x20-byte element of [first, last) into raw storage at dest
// (copy constructor 0xb01cb0); returns the end of the copied range.
#include "game/types.h"

struct Elem_b027b0 {
    char mData[0x20];
    Elem_b027b0(const Elem_b027b0& o);   // 0x00b01cb0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00b027b0
Elem_b027b0* UninitializedCopy_b027b0(const Elem_b027b0* first, const Elem_b027b0* last, Elem_b027b0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_b027b0(*first);
    return dest;
}
