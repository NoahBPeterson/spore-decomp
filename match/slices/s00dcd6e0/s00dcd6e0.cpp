// uninitialized_copy (0x00dcd6e0): copy-construct each 0x178-byte element of [first, last) into raw storage at dest
// (copy constructor 0xdcd590); returns the end of the copied range.
#include "game/types.h"

struct Elem_dcd6e0 {
    char mData[0x178];
    Elem_dcd6e0(const Elem_dcd6e0& o);   // 0x00dcd590
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00dcd6e0
Elem_dcd6e0* UninitializedCopy_dcd6e0(const Elem_dcd6e0* first, const Elem_dcd6e0* last, Elem_dcd6e0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_dcd6e0(*first);
    return dest;
}
