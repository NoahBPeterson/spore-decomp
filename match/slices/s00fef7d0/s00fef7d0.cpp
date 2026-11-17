// uninitialized_copy (0x00fef7d0): copy-construct each 0x38-byte element of [first, last) into raw storage at dest
// (copy constructor 0xfef730); returns the end of the copied range.
#include "game/types.h"

struct Elem_fef7d0 {
    char mData[0x38];
    Elem_fef7d0(const Elem_fef7d0& o);   // 0x00fef730
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00fef7d0
Elem_fef7d0* UninitializedCopy_fef7d0(const Elem_fef7d0* first, const Elem_fef7d0* last, Elem_fef7d0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_fef7d0(*first);
    return dest;
}
