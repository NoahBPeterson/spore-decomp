// uninitialized_copy (0x00bc56f0): copy-construct each 0x7b4-byte element of [first, last) into raw storage at dest
// (copy constructor 0xbc54f0); returns the end of the copied range.
#include "game/types.h"

struct Elem_bc56f0 {
    char mData[0x7b4];
    Elem_bc56f0(const Elem_bc56f0& o);   // 0x00bc54f0
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00bc56f0
Elem_bc56f0* UninitializedCopy_bc56f0(const Elem_bc56f0* first, const Elem_bc56f0* last, Elem_bc56f0* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_bc56f0(*first);
    return dest;
}
