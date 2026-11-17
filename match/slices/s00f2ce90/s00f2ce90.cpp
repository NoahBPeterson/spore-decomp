// uninitialized_copy (0x00f2ce90): copy-construct each 0x4e0-byte element of [first, last) into raw storage at dest
// (copy constructor 0xdfd080); returns the end of the copied range.
#include "game/types.h"

struct Elem_f2ce90 {
    char mData[0x4e0];
    Elem_f2ce90(const Elem_f2ce90& o);   // 0x00dfd080
    static void* operator new(size_t, void* p) throw() { return p; }
};

// @ 0x00f2ce90
Elem_f2ce90* UninitializedCopy_f2ce90(const Elem_f2ce90* first, const Elem_f2ce90* last, Elem_f2ce90* dest)
{
    for (; first != last; ++first, ++dest)
        new (dest) Elem_f2ce90(*first);
    return dest;
}
