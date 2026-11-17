// uninitialized_copy (0x007f6ea0): copy-construct each 0x8c-byte element of [first, last) into raw storage at dest
// (copy constructor 0x7f6df0); returns the end of the copied range.
#include "game/types.h"

struct Elem_7f6ea0 {
    char mData[0x8c];
    Elem_7f6ea0(const Elem_7f6ea0& o);   // 0x007f6df0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x007f6ea0
Elem_7f6ea0* UninitializedCopy_7f6ea0(const Elem_7f6ea0* first, const Elem_7f6ea0* last, Elem_7f6ea0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_7f6ea0(*first);
    return dest;
}
